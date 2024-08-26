#ifndef LPC845_H_
#define LPC845_H_

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;

#define   __I     	volatile const       /*!< Define permisos 'solo lectura' */

#define     __O     volatile             /*!< Define permisos 'solo escritura' */
#define     __IO    volatile             /*!< Define permisos 'lectura / escritura' */

/* Los siguientes defines deben usarce para miembros de estructuras */
#define     __IM     volatile const      /*! Define permisos 'solo lectura' para miembros de estructuras */
#define     __OM     volatile            /*! Define permisos 'solo escritura' para miembros de estructuras */
#define     __IOM    volatile            /*! Define permisos 'lectura / escritura' para miembros de estructuras */

/* ----------------------------------------------------------------------------
 -- Acceso a SYSCON
 ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Acceso a SYSCON
 * @{
 */

/** SYSCON - Tipo de datos bloque de Registros */
/** SYSCON - Tipo de datos bloque de Registros */
typedef struct {
	__IO uint32_t SYSMEMREMAP; /**< Registro de Remp del Sistema, offset: 0x0 */
	uint8_t RESERVED_0[4];
	__IO uint32_t SYSPLLCTRL; /**< Control de PLL, offset: 0x8 */
	__I uint32_t SYSPLLSTAT; /**< Status de PLL, offset: 0xC */
	uint8_t RESERVED_1[16];
	__IO uint32_t SYSOSCCTRL; /**< Control del oscilador del sistema, offset: 0x20 */
	__IO uint32_t WDTOSCCTRL; /**< Control del oscilador del Watchdog, offset: 0x24 */
	__IO uint32_t FROOSCCTRL; /**< Control del oscilador FRO, offset: 0x28 */
	uint8_t RESERVED_2[4];
	__IO uint32_t FRODIRECTCLKUEN; /**< Registro de habilitación de update de FRO como fuente directa de clock, offset: 0x30 */
	uint8_t RESERVED_3[4];
	__IO uint32_t SYSRSTSTAT; /**< Registro de estado de reset, offset: 0x38 */
	uint8_t RESERVED_4[4];
	__IO uint32_t SYSPLLCLKSEL; /**< Registro de selección de fuente de clock del System PLL, offset: 0x40 */
	__IO uint32_t SYSPLLCLKUEN; /**< Registro de habilitación de update de fuente de clock del System PLL, offset: 0x44 */
	__IO uint32_t MAINCLKPLLSEL; /**< Registro de selección de fuente de clock del Main clock PLL, offset: 0x48 */
	__IO uint32_t MAINCLKPLLUEN; /**< Registro de habilitación de update de fuente de clock del Main clock PLL, offset: 0x4C */
	__IO uint32_t MAINCLKSEL; /**< Registro de selección de fuente de clock del Main clock, offset: 0x50 */
	__IO uint32_t MAINCLKUEN; /**< Registro de habilitación de update de fuente de clock del Main clock, offset: 0x54 */
	__IO uint32_t SYSAHBCLKDIV; /**< Registro de divisor del System clock, offset: 0x58 */
	uint8_t RESERVED_5[4];
	__IO uint32_t CAPTCLKSEL; /**< Registro de selección de fuente de clock del CAPT, offset: 0x60 */
	__IO uint32_t ADCCLKSEL; /**< Registro de selección de fuente de clock del ADC, offset: 0x64 */
	__IO uint32_t ADCCLKDIV; /**< Registro de divisor del ADC clock, offset: 0x68 */
	__IO uint32_t SCTCLKSEL; /**< Registro de selección de fuente de clock del SCT clock, offset: 0x6C */
	__IO uint32_t SCTCLKDIV; /**< Registro de divisor del SCT clock, offset: 0x70 */
	__IO uint32_t EXTCLKSEL; /**< Registro de selección de fuente de clock externo, offset: 0x74 */
	uint8_t RESERVED_6[8];
	__IO uint32_t SYSAHBCLKCTRL0; /**< Registro de control del grupo 0 de clock, offset: 0x80 */
	__IO uint32_t SYSAHBCLKCTRL1; /**< Registro de control del grupo 1 de clock, offset: 0x84 */
	__IO uint32_t PRESETCTRL0; /**< Registro de control del grupo 0 de reset de Periféricos, offset: 0x88 */
	__IO uint32_t PRESETCTRL1; /**< Registro de control del grupo 1 de reset de Periféricos, offset: 0x8C */
	__IO uint32_t FCLKSEL[11]; /**< Registro de selección de fuente de clock de Periféricos. FCLK0SEL~FCLK4SEL son para elegir la fuente de clock UART0~UART4. FCLK5SEL~FCLK8SEL son para elegir la fuente de clock de I2C0~I2C3. FCLK9SEL~FCLK10SEL son para elegir la fuente de clock de SPI0~SPI1., array offset: 0x90, array step: 0x4 */
	uint8_t RESERVED_7[20];
	struct { /* offset: 0xD0, array step: 0x10 */
		__IO uint32_t FRGDIV; /**< Registro de valor de divisor N del generador fraccional, array offset: 0xD0, array step: 0x10 */
		__IO uint32_t FRGMULT; /**< Registro de valor de multiplicador N del generador fraccional, array offset: 0xD4, array step: 0x10 */
		__IO uint32_t FRGCLKSEL; /**< Registro de selección de fuente de clock de FRG N, array offset: 0xD8, array step: 0x10 */
		uint8_t RESERVED_0[4];
	} FRG[2];
	__IO uint32_t CLKOUTSEL; /**< Registro de selección de fuente de CLKOUT, offset: 0xF0 */
	__IO uint32_t CLKOUTDIV; /**< Registro de divisor de CLKOUT, offset: 0xF4 */
	uint8_t RESERVED_8[4];
	__IO uint32_t EXTTRACECMD; /**< Registro de comando del External trace buffer, offset: 0xFC */
	__I uint32_t PIOPORCAP[2]; /**< Estado de captura de POR PIO N(PIO0 tiene 32 PIOs, PIO1 tiene 22 PIOs), array offset: 0x100, array step: 0x4 */
	uint8_t RESERVED_9[44];
	__IO uint32_t IOCONCLKDIV6; /**< Clock 6 para filtro de glitch programable del IOCON, offset: 0x134 */
	__IO uint32_t IOCONCLKDIV5; /**< Clock 5 para filtro de glitch programable del IOCON, offset: 0x138 */
	__IO uint32_t IOCONCLKDIV4; /**< Clock 4 para filtro de glitch programable del IOCON, offset: 0x13C */
	__IO uint32_t IOCONCLKDIV3; /**< Clock 3 para filtro de glitch programable del IOCON, offset: 0x140 */
	__IO uint32_t IOCONCLKDIV2; /**< Clock 2 para filtro de glitch programable del IOCON, offset: 0x144 */
	__IO uint32_t IOCONCLKDIV1; /**< Clock 1 para filtro de glitch programable del IOCON, offset: 0x148 */
	__IO uint32_t IOCONCLKDIV0; /**< Clock 0 para filtro de glitch programable del IOCON, offset: 0x14C */
	__IO uint32_t BODCTRL; /**< Registro de control de BOD, offset: 0x150 */
	__IO uint32_t SYSTCKCAL; /**< Registro de calibración del System tick timer, offset: 0x154 */
	uint8_t RESERVED_10[24];
	__IO uint32_t IRQLATENCY; /**< Registro de latencia de IRQ, offset: 0x170 */
	__IO uint32_t NMISRC; /**< Registro de selección de fuente de NMI, offset: 0x174 */
	__IO uint32_t PINTSEL[8]; /**< Registro de selección de Pin interrupt N, array offset: 0x178, array step: 0x4 */
	uint8_t RESERVED_11[108];
	__IO uint32_t STARTERP0; /**< Registro 0 de habilitación de wake up por pin Start logic 0, offset: 0x204 */
	uint8_t RESERVED_12[12];
	__IO uint32_t STARTERP1; /**< Registro 1 de habilitación de wake up por pin Start logic 0, offset: 0x214 */
	uint8_t RESERVED_13[24];
	__IO uint32_t PDSLEEPCFG; /**< Registro de configuración de Deep-sleep, offset: 0x230 */
	__IO uint32_t PDAWAKECFG; /**< Registro de configuración de Wake-up, offset: 0x234 */
	__IO uint32_t PDRUNCFG; /**< Registro de configuración de Power, offset: 0x238 */
	uint8_t RESERVED_14[444];
	__I uint32_t DEVICE_ID; /**< Registro de configuración de Part ID, offset: 0x3F8 */
} SYSCON_Type;

/*! @name SYSAHBCLKCTRL0 - Registro de control de grupo 0 de System clock */
/*! @{ */
#define SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK        (0x40U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO0_SHIFT       (6U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK        (0x100000U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO1_SHIFT       (20U)
#define SYSCON_SYSAHBCLKCTRL0_IOCON_MASK		(0x40000)
#define SYSCON_SYSAHBCLKCTRL0_IOCON_SHIFT		(18U)

/* SYSCON - Dirección  base de la instancia del Periférico */
/** Dirección  base de Periférico SYSCON */
#define SYSCON_BASE                              (0x40048000u)
/** Puntero base de Periférico SYSCON */
#define SYSCON                                   ((SYSCON_Type *)SYSCON_BASE)
/** Array inicializador de Dirección  base de Periférico SYSCON */

/* ----------------------------------------------------------------------------
 -- Acceso a IOCON
 ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Acceso a IOCON
 * @{
 */

/** IOCON - Tipo de datos bloque de Registros */
typedef struct {
	__IO uint32_t PIO[56]; /**< Control Digital de los pines de I/O PIO0_31 y PIO1_10, array offset: 0x0, array step: 0x4 */
} IOCON_Type;

/* ----------------------------------------------------------------------------
 -- IOCON máscaras de registros
 ---------------------------------------------------------------------------- */

/*!
 * @addtogroup máscaras de registros
 * @{
 */

/*! @name PIO - Control Digital de los pines de I/O PIO0_31 y PIO1_10 */
/*! @{ */
#define IOCON_PIO_MODE_MASK                      (0x18U)
#define IOCON_PIO_MODE_SHIFT                     (3U)
/*! MODE - Elije el modo del pin (control de resistencia interna de pull-up/pull-down).
 *  0b00..Inactivo. No pull-down/pull-up.
 *  0b01..Pull-down.
 *  0b10..Pull-up.
 *  0b11..Modo Repetidor.
 */
#define IOCON_PIO_HYS_MASK                       (0x20U)
#define IOCON_PIO_HYS_SHIFT                      (5U)
/*! HYS - Histéresis.
 *  0b0..Disable
 *  0b1..Enable
 */
#define IOCON_PIO_INV_MASK                       (0x40U)
#define IOCON_PIO_INV_SHIFT                      (6U)
/*! INV - Inversión de entrada
 *  0b0..Entrada no invertida (Alto en pin se lee como 1; LOW en pin se lee como 0).
 *  0b1..Entrada invertida (Alto en pin se lee como 0; LOW en pin se lee como 1).
 */
#define IOCON_PIO_I2CMODE_MASK                   (0x300U)
#define IOCON_PIO_I2CMODE_SHIFT                  (8U)
/*! I2CMODE - Selección de modo I2C.
 *  0b00..Modo estandar/ Modo Fast I2C.
 *  0b01..Funcionalidad estandar de GPIO. Requiere pull-up externa para función GPIO.
 *  0b10..Modo I2C Fast Plus
 *  0b11..Reservado
 */
#define IOCON_PIO_OD_MASK                        (0x400U)
#define IOCON_PIO_OD_SHIFT                       (10U)
#define IOCON_PIO_OD_(x)						 (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_OD_SHIFT)) & IOCON_PIO_OD_MASK)

/*! OD - Modo Open-drain.
 *  0b0..Disable.
 *  0b1..Modo Open-drain enabled. Nota: No es true open-drain.
 */
#define IOCON_PIO_MODE(x)                        (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_MODE_SHIFT)) & IOCON_PIO_MODE_MASK)
#define IOCON_PIO_S_MODE_MASK                    (0x1800U)
#define IOCON_PIO_S_MODE_SHIFT                   (11U)
/*! S_MODE - Modo de muestreo de filtro digital.
 *  0b00..Bypass input filter.
 *  0b01..1 ciclo de clock. Los pulsos de entrada más angostos que 1 ciclo de clock del filtro son rechazados.
 *  0b10..2 ciclo de clock. Los pulsos de entrada más angostos que 2 ciclo de clock del filtro son rechazados.
 *  0b11..3 ciclo de clock. Los pulsos de entrada más angostos que 3 ciclo de clock del filtro son rechazados.
 */
#define IOCON_PIO_CLK_DIV_MASK                   (0xE000U)
#define IOCON_PIO_CLK_DIV_SHIFT                  (13U)
/*! CLK_DIV - Selección de divisor de clock para el clock de muestreo del filtro de entrada. Valor 0x7 está reservado.
 *  0b000..IOCONCLKDIV0
 *  0b001..IOCONCLKDIV1
 *  0b010..IOCONCLKDIV2
 *  0b011..IOCONCLKDIV3
 *  0b100..IOCONCLKDIV4
 *  0b101..IOCONCLKDIV5
 *  0b110..IOCONCLKDIV6
 */
#define IOCON_PIO_DACMODE_MASK                   (0x10000U)
#define IOCON_PIO_DACMODE_SHIFT                  (16U)
/*! DACMODE - Modo DAC enable.
 *  0b0..Disable.
 *  0b1..Enable.
 */
/*! @} */

/* Cantidad de IOCON_PIO */
#define IOCON_PIO_COUNT                          (56U)

/*!
 * @}
 *//* Fin de máscaras de registros de IOCON */

/* IOCON - Dirección base de la instancia del periférico */
/** Dirección base del periférico IOCON */
#define IOCON_BASE                               (0x40044000u)
/** Puntero a la base del periférico IOCON */
#define IOCON                                    ((IOCON_Type *)IOCON_BASE)
/** Array inicializador de la dirección base de IOCON */
#define IOCON_BASE_ADDRS                         { IOCON_BASE }
/** Array inicializador del puntero de IOCON */
#define IOCON_BASE_PTRS                          { IOCON }

#define    IOCON_INDEX_PIO0_17       ( 0)
#define    IOCON_INDEX_PIO0_13       ( 1)
#define    IOCON_INDEX_PIO0_12       ( 2)
#define    IOCON_INDEX_PIO0_5        ( 3)
#define    IOCON_INDEX_PIO0_4        ( 4)
#define    IOCON_INDEX_PIO0_3        ( 5)
#define    IOCON_INDEX_PIO0_2        ( 6)
#define    IOCON_INDEX_PIO0_11       ( 7)
#define    IOCON_INDEX_PIO0_10       ( 8)
#define    IOCON_INDEX_PIO0_16       ( 9)
#define    IOCON_INDEX_PIO0_15       (10)
#define    IOCON_INDEX_PIO0_1        (11)
#define    IOCON_INDEX_PIO0_9        (13)
#define    IOCON_INDEX_PIO0_8        (14)
#define    IOCON_INDEX_PIO0_7        (15)
#define    IOCON_INDEX_PIO0_6        (16)
#define    IOCON_INDEX_PIO0_0        (17)
#define    IOCON_INDEX_PIO0_14       (18)
#define    IOCON_INDEX_PIO0_28       (20)
#define    IOCON_INDEX_PIO0_27       (21)
#define    IOCON_INDEX_PIO0_26       (22)
#define    IOCON_INDEX_PIO0_25       (23)
#define    IOCON_INDEX_PIO0_24       (24)
#define    IOCON_INDEX_PIO0_23       (25)
#define    IOCON_INDEX_PIO0_22       (26)
#define    IOCON_INDEX_PIO0_21       (27)
#define    IOCON_INDEX_PIO0_20       (28)
#define    IOCON_INDEX_PIO0_19       (29)
#define    IOCON_INDEX_PIO0_18       (30)
#define    IOCON_INDEX_PIO1_8        (31)
#define    IOCON_INDEX_PIO1_9        (32)
#define    IOCON_INDEX_PIO1_0        (36)
#define    IOCON_INDEX_PIO1_1        (37)
#define    IOCON_INDEX_PIO1_2        (38)
#define    IOCON_INDEX_PIO1_3        (41)
#define    IOCON_INDEX_PIO1_4        (42)
#define    IOCON_INDEX_PIO1_5        (43)
#define    IOCON_INDEX_PIO1_6        (46)
#define    IOCON_INDEX_PIO1_7        (49)

/*!
 * @}
 *//* Final del bloque de acceso a IOCON */

/* ----------------------------------------------------------------------------
 -- Acceso a GPIO
 ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Acceso a GPIO
 * @{
 */

/** GPIO - Register Layout Typedef */
typedef struct {
	__IO uint8_t B[2][32]; /**< Registros de acceso a los pines de a Byte para port 0 y 1, array offset: 0x0, array step: index*0x20, index2*0x1 */
	uint8_t RESERVED_0[4032];
	__IO uint32_t W[2][32]; /**< Registros de acceso a los pines de a Word para port 0 y 1, array offset: 0x1000, array step: index*0x80, index2*0x4 */
	uint8_t RESERVED_1[3840];
	__IO uint32_t DIR[2]; /**< Registros de Dirección, array offset: 0x2000, array step: 0x4 */
	uint8_t RESERVED_2[120];
	__IO uint32_t MASK[2]; /**< Registros de Máscara, array offset: 0x2080, array step: 0x4 */
	uint8_t RESERVED_3[120];
	__IO uint32_t PIN[2]; /**< Registros de pines de los puertos, array offset: 0x2100, array step: 0x4 */
	uint8_t RESERVED_4[120];
	__IO uint32_t MPIN[2]; /**< Registros enmascarados de los puertos, array offset: 0x2180, array step: 0x4 */
	uint8_t RESERVED_5[120];
	__IO uint32_t SET[2]; /**< Set port, array offset: 0x2200, array step: 0x4 */
	uint8_t RESERVED_6[120];
	__O uint32_t CLR[2]; /**< Clear port, array offset: 0x2280, array step: 0x4 */
	uint8_t RESERVED_7[120];
	__O uint32_t NOT[2]; /**< Toggle port, array offset: 0x2300, array step: 0x4 */
	uint8_t RESERVED_8[120];
	__O uint32_t DIRSET[2]; /**< Set bits de dirección para el puerto, array offset: 0x2380, array step: 0x4 */
	uint8_t RESERVED_9[120];
	__O uint32_t DIRCLR[2]; /**< Clear bits de dirección para el puerto, array offset: 0x2400, array step: 0x4 */
	uint8_t RESERVED_10[120];
	__O uint32_t DIRNOT[2]; /**< Toggle bits de dirección para el puerto, array offset: 0x2480, array step: 0x4 */
} GPIO_Type;

/* ----------------------------------------------------------------------------
 -- Máscaras registros de GPIO
 ---------------------------------------------------------------------------- */

/* GPIO - Dirección de base de la instancia de periferico */
/** Dirección de base de periférico GPIO */
#define GPIO_BASE                                (0x0A0000000u)
/** Puntero a la base de periférico GPIO */
#define GPIO                                     ((GPIO_Type *)GPIO_BASE)

/*!
 * @}
 *//* Final del bloque de acceso a IOCON  */

/*!
 * @addtogroup NVIC_Peripheral_Access_Layer NVIC Peripheral Access Layer
 * @{
 */
/**
 \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
/** NVIC - Register Layout Typedef */
typedef struct {
	__IO uint32_t ISER[1U]; /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
	uint32_t RESERVED0[31U]; /**<RESERVATED. NOT USED */
	__IO uint32_t ICER[1U]; /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
	uint32_t RSERVED1[31U]; /**<RESERVATED. NOT USED */
	__IO uint32_t ISPR[1U]; /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
	uint32_t RESERVED2[31U]; /**<RESERVATED. NOT USED */
	__IO uint32_t RESERVED3[31U]; /**<RESERVATED. NOT USED */
	uint32_t RESERVED4[64U]; /**<RESERVATED. NOT USED */
	__IO uint32_t IP[8U]; /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
} NVIC_Type; /** Registers for the NVIC */

/* Memory mapping of Core Hardware */
/** System Control Space Base Address */
#define SCS_BASE            (0xE000E000UL)
/** SysTick Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)
/** NVIC Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)
/** System Control Block Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)
/** NVIC configuration struct */
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )
/*!
 * @}
 */

/*!
 * @addtogroup PIN_INT_Peripheral_Access_Layer PIN_INT Peripheral Access Layer
 * @{
 */
/**
 \brief  Structure type to access the Pin Interrupt.
 */
/** PIN_INTERRUPT - Register Layout Typedef */
typedef struct {
	__IO uint32_t ISEL; /**< ASSIGN LEVEL SENSITIVE OR EDGE SENSITIVE*/

	__IO uint32_t IENR; /**< Enables rising-edge interrupts.*/
	__O uint32_t SIENR; /**< Write to enable rising-edge interrupts*/
	__O uint32_t CIENR; /**< Write to disable rising-edge interrupts.*/

	__IO uint32_t IENF; /**< Enables falling-edge interrupts */
	__O uint32_t SIENF; /**< Write to enable falling-edge interrupts.*/
	__O uint32_t CIENF; /**< Write to disable falling-edge interrupts*/

	__IO uint32_t RISE; /**< GIVES WHITCH PORTS HAVE DETECTED A RISING EDGE*/
	__IO uint32_t FALL; /**< GIVES WHITCH PORTS HAVE DETECTED A FALLING EDGE*/
	__IO uint32_t IST; /**< GIVES WITCH PINES HAVE A INTERRUPT REQUEST*/

	__IO uint32_t PMCTRL; /**< Pattern match interrupt control register */
	__IO uint32_t PMSRC; /**< Pattern match interrupt bit-slice source register*/
	__IO uint32_t PMCFG; /**< Pattern match interrupt bit slice configuration register*/
} PIN_INTERRUPT_t; /** Registers for the PIN_INTERRUPT */

#define PIN_INTERRUPT ( (PIN_INTERRUPT_t *) 0xA0004000UL )
/*!
 * @}
 */

/*! @name PDRUNCFG - Power configuration register */
/*! @{ */
#define SYSCON_PDRUNCFG_FROOUT_PD_MASK           (0x1U)
#define SYSCON_PDRUNCFG_FROOUT_PD_SHIFT          (0U)
/*! FROOUT_PD - FRO oscillator output wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_FROOUT_PD(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_FROOUT_PD_SHIFT)) & SYSCON_PDRUNCFG_FROOUT_PD_MASK)
#define SYSCON_PDRUNCFG_FRO_PD_MASK              (0x2U)
#define SYSCON_PDRUNCFG_FRO_PD_SHIFT             (1U)
/*! FRO_PD - FRO oscillator power-down wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_FRO_PD(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_FRO_PD_SHIFT)) & SYSCON_PDRUNCFG_FRO_PD_MASK)
#define SYSCON_PDRUNCFG_FLASH_PD_MASK            (0x4U)
#define SYSCON_PDRUNCFG_FLASH_PD_SHIFT           (2U)
/*! FLASH_PD - Flash wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_FLASH_PD(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_FLASH_PD_SHIFT)) & SYSCON_PDRUNCFG_FLASH_PD_MASK)
#define SYSCON_PDRUNCFG_BOD_PD_MASK              (0x8U)
#define SYSCON_PDRUNCFG_BOD_PD_SHIFT             (3U)
/*! BOD_PD - BOD wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_BOD_PD(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_BOD_PD_SHIFT)) & SYSCON_PDRUNCFG_BOD_PD_MASK)
#define SYSCON_PDRUNCFG_ADC_PD_MASK              (0x10U)
#define SYSCON_PDRUNCFG_ADC_PD_SHIFT             (4U)
/*! ADC_PD - ADC wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_ADC_PD(x)                (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_ADC_PD_SHIFT)) & SYSCON_PDRUNCFG_ADC_PD_MASK)
#define SYSCON_PDRUNCFG_SYSOSC_PD_MASK           (0x20U)
#define SYSCON_PDRUNCFG_SYSOSC_PD_SHIFT          (5U)
/*! SYSOSC_PD - Crystal oscillator wake-up configuration
 *  0b0..powered
 *  0b1..powered down
 */
#define SYSCON_PDRUNCFG_SYSOSC_PD(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_SYSOSC_PD_SHIFT)) & SYSCON_PDRUNCFG_SYSOSC_PD_MASK)
#define SYSCON_PDRUNCFG_WDTOSC_PD_MASK           (0x40U)
#define SYSCON_PDRUNCFG_WDTOSC_PD_SHIFT          (6U)
/*! WDTOSC_PD - Watchdog oscillator wake-up configuration. Changing this bit to powered-down has no
 *    effect when the LOCK bit in the WWDT MOD register is set. In this case, the watchdog
 *    oscillator is always running
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDRUNCFG_WDTOSC_PD(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_WDTOSC_PD_SHIFT)) & SYSCON_PDRUNCFG_WDTOSC_PD_MASK)
#define SYSCON_PDRUNCFG_SYSPLL_PD_MASK           (0x80U)
#define SYSCON_PDRUNCFG_SYSPLL_PD_SHIFT          (7U)
/*! SYSPLL_PD - System PLL wake-up configuration
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDRUNCFG_SYSPLL_PD(x)             (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_SYSPLL_PD_SHIFT)) & SYSCON_PDRUNCFG_SYSPLL_PD_MASK)
#define SYSCON_PDRUNCFG_DAC0_MASK                (0x2000U)
#define SYSCON_PDRUNCFG_DAC0_SHIFT               (13U)
/*! DAC0 - DAC0 wake-up configuration
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDRUNCFG_DAC0(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_DAC0_SHIFT)) & SYSCON_PDRUNCFG_DAC0_MASK)
#define SYSCON_PDRUNCFG_DAC1_MASK                (0x4000U)
#define SYSCON_PDRUNCFG_DAC1_SHIFT               (14U)
/*! DAC1 - DAC1 wake-up configuration
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDRUNCFG_DAC1(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_DAC1_SHIFT)) & SYSCON_PDRUNCFG_DAC1_MASK)
#define SYSCON_PDRUNCFG_ACMP_MASK                (0x8000U)
#define SYSCON_PDRUNCFG_ACMP_SHIFT               (15U)
/*! ACMP - Analog comparator wake-up configuration
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define SYSCON_PDRUNCFG_ACMP(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_PDRUNCFG_ACMP_SHIFT)) & SYSCON_PDRUNCFG_ACMP_MASK)
/*! @} */

/*! @name FRODIRECTCLKUEN - FRO direct clock source update enable register */
/*! @{ */
#define SYSCON_FRODIRECTCLKUEN_ENA_MASK          (0x1U)
#define SYSCON_FRODIRECTCLKUEN_ENA_SHIFT         (0U)
/*! ENA - Enable fro clock source update
 *  0b0..no change
 *  0b1..update clock source
 */
#define SYSCON_FRODIRECTCLKUEN_ENA(x)            (((uint32_t)(((uint32_t)(x)) << SYSCON_FRODIRECTCLKUEN_ENA_SHIFT)) & SYSCON_FRODIRECTCLKUEN_ENA_MASK)

/*! @name EXTCLKSEL - external clock source select register */
/*! @{ */
#define SYSCON_EXTCLKSEL_SEL_MASK                (0x1U)
#define SYSCON_EXTCLKSEL_SEL_SHIFT               (0U)
/*! SEL - Clock source for external clock
 *  0b0..System oscillator
 *  0b1..Clk_in
 */
#define SYSCON_EXTCLKSEL_SEL(x)                  (((uint32_t)(((uint32_t)(x)) << SYSCON_EXTCLKSEL_SEL_SHIFT)) & SYSCON_EXTCLKSEL_SEL_MASK)
/*! @} */

/*! @name MAINCLKPLLSEL - Main clock source select register */
/*! @{ */
#define SYSCON_MAINCLKPLLSEL_SEL_MASK            (0x3U)
#define SYSCON_MAINCLKPLLSEL_SEL_SHIFT           (0U)
/*! SEL - System PLL clock source
 *  0b00..main_clk_pre_pll
 *  0b01..sys pll
 *  0b10..none
 *  0b11..none
 */
#define SYSCON_MAINCLKPLLSEL_SEL(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKPLLSEL_SEL_SHIFT)) & SYSCON_MAINCLKPLLSEL_SEL_MASK)
/*! @} */

/*! @name MAINCLKUEN - Main clock source update enable register */
/*! @{ */
#define SYSCON_MAINCLKUEN_ENA_MASK               (0x1U)
#define SYSCON_MAINCLKUEN_ENA_SHIFT              (0U)
/*! ENA - Enable main clock source update
 *  0b0..no change
 *  0b1..update clock source
 */
#define SYSCON_MAINCLKUEN_ENA(x)                 (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKUEN_ENA_SHIFT)) & SYSCON_MAINCLKUEN_ENA_MASK)
/*! @} */

/*! @name MAINCLKPLLUEN - Main clock source update enable register */
/*! @{ */
#define SYSCON_MAINCLKPLLUEN_ENA_MASK            (0x1U)
#define SYSCON_MAINCLKPLLUEN_ENA_SHIFT           (0U)
/*! ENA - Enable main clock source update
 *  0b0..no change
 *  0b1..update clock source
 */
#define SYSCON_MAINCLKPLLUEN_ENA(x)              (((uint32_t)(((uint32_t)(x)) << SYSCON_MAINCLKPLLUEN_ENA_SHIFT)) & SYSCON_MAINCLKPLLUEN_ENA_MASK)
/*! @} */

/*! @brief FRO clock setting API address in ROM. */
#define CLOCK_FRO_SETTING_API_ROM_ADDRESS (0x0F0026F5U)
#define BOARD_BOOTCLOCKRUN_CORE_CLOCK              30000000U  /*!< Core clock frequency: 30000000Hz */

#endif
