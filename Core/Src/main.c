/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN PD */

	uint8_t IT[1] ={0}; //Interruption
	uint8_t brk= 0;    // Break validation

	//Counter variable / Plate position marker
	int cont = 0;

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/*
 * Setting the plate velocity with the Dip-Switch
 *
 */

int gameplay()
{

	//velocity variable.

	int velocity = 0;

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)) //First Switch

	{
	    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)) //Second Switch

	    {

	        if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)) //Thrid Switch

	        {
	            velocity = 500; //Super Fast

	        }
	        else
	        {
	        	velocity = 1000; //Fast
	        }
	    }

	  else

	    {
	        velocity = 1500; //Medium
	    }
	}

	  else
	  {

		velocity = 2000; //Slow
	  }

	return velocity; //Variable Exit
}


/*
 * Setting the shooting configuration (amount of shots the players can make)
 */

int shoot()
{
	//Shooting variable

	int shoot = 0;

	//available shots

		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)) //Fourth Switch (levels)
		{
			shoot = 11; //If it's DOWN
		}
		else
		{
			shoot = 25; //If it's UP
		}

		return shoot; //Variable Exit

}


/*
 * Plate and underscores printing
 */

int plate(int time, int rounds, int score){

//Space buffer

char buffspace;

//Loop till level selected

for(int i = 1; i <= rounds; i++)
{

	/*
	 * BUFFER VARIABLES: These buffers help to store the ASCII values of the integers
	 */

	char buffrounds[16];
	char buffi[16];
	char buffpoints[16];

	/*
	 * "Tiro" Transmission
	 * */
	HAL_UART_Transmit(&huart2, "\n\rTiro: ", 8 , HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, buffi,sprintf(buffi,"%d",i), 500);
	HAL_UART_Transmit(&huart2, " de ", 4 , HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, buffrounds, sprintf(buffrounds,"%d",rounds), 500);
	HAL_UART_Transmit(&huart2, "\n", 1 , HAL_MAX_DELAY);


	/*
	 * "Puntuacion" Transmission
	 * */
	HAL_UART_Transmit(&huart2, "\rPuntuacion: ", 13, HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, buffpoints, sprintf(buffpoints,"%02d",score), 500);
	HAL_UART_Transmit(&huart2, "\n", 1 , HAL_MAX_DELAY);

	/*
	 * Rail and Plate Transmission // 'Space' key to start printing plus the interruption validations
	 * */
	HAL_UART_Transmit(&huart2, "\r_\t_\t_\t_\t_\t_\t_\t*\t_\t_\t\n", 24, HAL_MAX_DELAY);

	HAL_UART_Receive(&huart2, buffspace , 1, HAL_MAX_DELAY); //'SPACE' receiver

	HAL_UART_Transmit(&huart2, "\r@", 2, HAL_MAX_DELAY);
	cont++;
	if(brk != 0)
	{
	  brk = 0;
	  break;
	}
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_Delay(time);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, " ",  1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t@",2, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	cont++;
	if(brk != 0)
		{
		  brk = 0;
		  break;
		}
	HAL_UART_Receive_IT (&huart2, IT, 1);
	HAL_Delay(time);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t ", 2, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t@", 3, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	cont++;
	if(brk != 0)
		{
		  brk = 0;
		  break;
		}
	HAL_UART_Receive_IT (&huart2, IT, 1);
	HAL_Delay(time);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t ", 3, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t@", 4, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	cont++;
	if(brk != 0)
		{
		  brk = 0;
		  break;
		}
	HAL_UART_Receive_IT (&huart2, IT, 1);
	HAL_Delay(time);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t ", 4, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t@",5, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	cont++;
	if(brk != 0)
		{
		  brk = 0;
		  break;
		}
	HAL_UART_Receive_IT (&huart2, IT, 1);
	HAL_Delay(time);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t ", 5, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t\t@", 6, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	cont++;
	if(brk != 0)
		{
		  brk = 0;
		  break;
		}
	HAL_UART_Receive_IT (&huart2, IT, 1);
	HAL_Delay(time);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t\t ", 6, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t@", 7, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	cont++;
	if(brk != 0)
		{
		  brk = 0;
		  break;
		}
	HAL_UART_Receive_IT (&huart2, IT, 1);
	HAL_Delay(time);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t ", 7, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t@", 8, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	cont++;
	if(brk != 0)
		{
		  brk = 0;
		  break;
		}
	HAL_UART_Receive_IT (&huart2, IT, 1);
	HAL_Delay(time);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t ", 8, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t\t@", 9, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	cont++;
	if(brk != 0)
		{
		  brk = 0;
		  break;
		}
	HAL_UART_Receive_IT (&huart2, IT, 1);
	HAL_Delay(time);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t\t ", 9, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t\t\t@", 10, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	cont++;
	if(brk != 0)
		{
		  brk = 0;
		  break;
		}
	HAL_UART_Receive_IT (&huart2, IT, 1);
	HAL_Delay(time);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
	HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t\t\t ", 10, HAL_MAX_DELAY);
	HAL_UART_Receive_IT (&huart2, IT, 1); //Interrupt
}



}

/* USER CODE END 0 */

int main(void)
{

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /*
   * Function variable receivers for init
   * */
  int velocity_1;
  int shoot_1;
  char num = "a"; //'ENTER' key buffer
  int score_1 = 0;

  /*
   * Welcome Message
   * */
  HAL_UART_Transmit(&huart2, "\n\rBienvenido a tiro al plato!\n", 28 , HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, "\n\rConfigure la velocidad y el nivel utilizando el dip-switch de cuatro posiciones.\n", 82 , HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, "\n\rCuando esté listo, presione ENTER para comenzar!\n ", 52 , HAL_MAX_DELAY);

  //Initialization of the functions
  velocity_1 = gameplay();
  shoot_1 = shoot();


  HAL_UART_Receive(&huart2, num , 1, HAL_MAX_DELAY); //ENTER receiver


  plate(velocity_1,shoot_1, score_1); //GAME EXECUTION

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



  }
  /* USER CODE END 3 */


}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	int puntuacion; //Score variable (LITERALLY!!!)

	  if(cont == 8)
	  {

		puntuacion++;

	    for(int i = 0; i<=4; i++)
	    {
	    HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t ", 8, HAL_MAX_DELAY);
		HAL_Delay(500);
		HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t@", 8, HAL_MAX_DELAY);
	    }

	  }

	  else if (cont == 1)
	  {

	    for(int i = 0; i<=4; i++)
	    {

	    HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, " ",  1, HAL_MAX_DELAY);
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "@", 1, HAL_MAX_DELAY);
	    }

	  }

	  else if (cont == 2)
	  {

	    for(int i = 0; i<=4; i++)
	    {

	    HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t ",  2, HAL_MAX_DELAY);
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t@", 2, HAL_MAX_DELAY);
	    }

	  }

	  else if (cont == 3)
	  {

	    for(int i = 0; i<=4; i++)
	    {

	    HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t ",  3, HAL_MAX_DELAY);
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t@", 3, HAL_MAX_DELAY);
	    }

	  }

	  else if (cont == 4)
	  {

	    for(int i = 0; i<=4; i++)
	    {

	    HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t ",  4, HAL_MAX_DELAY);
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t@", 4, HAL_MAX_DELAY);

	    }
	  }

	  else if (cont == 5)
	  {

	    for(int i = 0; i<=4; i++)
	    {

	    HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t ",  5, HAL_MAX_DELAY);
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t@", 5, HAL_MAX_DELAY);

	    }

	  }

	  else if (cont == 6)
	  {

	    for(int i = 0; i<=4; i++)
	    {

	    HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t\t ",  6, HAL_MAX_DELAY);
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t\t@", 6, HAL_MAX_DELAY);

	    }
	  }

	  else if (cont == 7)
	  {

	    for(int i = 0; i<=4; i++)
	    {

	    HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t ",  7, HAL_MAX_DELAY);
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t@", 7, HAL_MAX_DELAY);

	    }
	  }

	  else if (cont == 9)
	  {
	    for(int i = 0; i<=4; i++)
	    {
	    HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t\t ",  9, HAL_MAX_DELAY);
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t\t@", 9, HAL_MAX_DELAY);
	    }
	  }
	 else
	  {
	    for(int i = 0; i<=4; i++)
	    {

	    HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t\t\t ",  10, HAL_MAX_DELAY);
		HAL_Delay(1000);
		HAL_UART_Transmit(&huart2, "\r", 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, "\t\t\t\t\t\t\t\t\t@",10, HAL_MAX_DELAY);

	    }
	  }
		//brk++;

		if(puntuacion >= 8)
		{
			__NOP();
		}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
