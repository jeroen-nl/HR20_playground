
// AVR LibC includes
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/version.h>




// typedefs

// vars
static uint8_t state_ADC;
bool sleep_with_ADC=0;


/*!
 *******************************************************************************
 *  Get temperature
 *
 *  \returns temperature in 1/100 degrees Celsius (1987: 19,87?C)
 *
 *  \note
 *  - measurment has been performed before using \ref ADC_Measure_Temp
 *  - Attention: negative values are possible 
 ******************************************************************************/
#if 0
int16_t ADC_Get_Temp_Degree(void)            // Get Temperature in 1/100 Deg ?C
{
    int32_t degree;

    degree = ADC_Convert_To_Degree();    
     
    if (degree < INT16_MIN){
        return (INT16_MIN);
    }else if (degree > INT16_MAX){ 
        return (INT16_MAX);
    }else{ 
        return ((int16_t) degree);        
    }
}
#endif
 

/*!
 *******************************************************************************
 *  Get battery voltage
 *
 *  \returns battery voltage in mV
 *
 *  \note
 *  - measurment has been performed before using \ref ADC_Measure_Ub
 *  - Battery voltage = (V_ref * 1024) / ADC_Val_Ub with V_ref=1.1V
 ******************************************************************************/
static int16_t ADC_Get_Bat_Voltage(uint16_t adc)             // Get Batteriy Voltage in mV
{
    uint32_t millivolt;
    millivolt = 1126400;
    millivolt /= adc; 
    return ((int16_t) millivolt);
}


/*!
 *******************************************************************************
 *  Get battery status
 *
 *  \returns false if battery is low
 *
 *  \note
 *  - none
 ******************************************************************************/
#if 0
bool ADC_Get_Bat_isOk(void)
{
	return (ADC_Get_Bat_Voltage() > ADC_LOW_BATT_LEVEL);
}
#endif

/*!
 *******************************************************************************
 *  convert ACD value to temperature 
 *
 *  \returns temperature in 1/100 degrees Celsius
 *
 *  \todo: store values for conversion in EEPROM 
 ******************************************************************************/
static int16_t ADC_Convert_To_Degree(int16_t adc)
{
    int16_t dummy;
    uint8_t i;
    int16_t kx=TEMP_CAL_OFFSET+(int16_t)kx_d[0];
    for (i=1; i<TEMP_CAL_N-1; i++){
        if (adc<kx+kx_d[i]){
            break;
        } else {       
            kx+=kx_d[i];
        }
    } // if condintion in loop is not reach i==TEMP_CAL_N-1

    /*! dummy never overload int16_t 
     *  check values for this condition / prevent overload
     *        values in kx_d[1]..kx_d[TEMP_CAL_N-1] is >=16 see to \ref ee_config 
     *        ADC value is <1024 (OK, only 10-bit AD converter)
     */
    dummy = (int16_t) (
            (((int32_t)(adc - kx))*(-TEMP_CAL_STEP))
            /(int32_t)(kx_d[i])
    ); 

    dummy += TEMP_CAL_N*TEMP_CAL_STEP-((int16_t)(i-1))*TEMP_CAL_STEP;
#if TEMP_COMPENSATE_OPTION
    dummy += (int16_t)config.room_temp_offset*10;
#endif

    return (dummy);        
}


/*!
 *******************************************************************************
 * ADC task
 * \note
 ******************************************************************************/
void start_task_ADC(void) {
	state_ADC=1;
	// power up ADC
	power_up_ADC();

    // set ADC control and status register
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADIE);         // prescaler=16
    
    // free running mode, (not needed, because auto trigger disabled)
    ADCSRB = 0;

	ADMUX = ADC_UB_MUX | (1<<REFS0);
	sleep_with_ADC=1;
}
#define ADC_TOLERANCE 3
static int16_t dummy_adc=0;
/*!
 *******************************************************************************
 * ADC task
 ******************************************************************************/
bool task_ADC(void) {
	switch (state_ADC) {
	case 1: //step 1
	    // set ADC control and status register
    	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS0)|(1<<ADIE); // prescaler=32
		// ADC conversion from 1 (battery is done)
		// first conversion put to trash
		// start new with same configuration;
		break;
	case 3: //step 3
		{	
			int16_t ad = ADCW;
            if ((ad>dummy_adc+ADC_TOLERANCE)||(ad<dummy_adc-ADC_TOLERANCE)) { 
                // adc noise protection, repeat measure
                REPEAT_ADC:
                dummy_adc=ad;
				sleep_with_ADC=true;
                return true;
            }
			#if DEBUG_BATT_ADC
				COM_printStr16(PSTR("batAD x"),ad);
			#endif
			update_ring(BAT_RING_TYPE,ADC_Get_Bat_Voltage(ad));

			// activate voltage divider
			ADC_ACT_TEMP_P |= (1<<ADC_ACT_TEMP);
			ADMUX = ADC_TEMP_MUX | (1<<REFS0);
		}
		break;
	case 2: //step 2
	case 4: //step 4
        dummy_adc = ADCW;
	    break;
	case 5: //step 5
        {
            int16_t ad = ADCW;
            if ((ad>dummy_adc+ADC_TOLERANCE)||(ad<dummy_adc-ADC_TOLERANCE)) { 
                // adc noise protection, repeat measure
                goto REPEAT_ADC; // optimization
            }
            int16_t t = ADC_Convert_To_Degree(ad);
            update_ring(TEMP_RING_TYPE,t);
            #if DEBUG_PRINT_MEASURE
                COM_debug_print_temperature(t);
            #endif
            shift_ring();
        }
        // do not use break here
	default:
		// deactivate voltage divider
    	ADC_ACT_TEMP_P &= ~(1<<ADC_ACT_TEMP);
	    // set ADC control and status register / disable ADC
	    ADCSRA = (0<<ADEN)|(1<<ADPS2)|(1<<ADPS0)|(1<<ADIE); 
		// power down ADC
		power_down_ADC();
		return false;
	}
	state_ADC++;
	sleep_with_ADC=true;
	return true;
}

