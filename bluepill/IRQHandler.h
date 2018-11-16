#ifndef IRQHANDLER_H_
#define IRQHANDLER_H_

#define RX_FRAME_SIZE					100
#define	RX_FRAME_START_BYTE				'$'
#define	RX_FRAME_END_BYTE				'\r'

extern "C" void TIM3_IRQHandler(void);
extern "C" void TIM4_IRQHandler(void);
extern "C" void EXTI0_IRQHandler(void);
extern "C" void EXTI15_10_IRQHandler(void);
extern "C" void USART3_IRQHandler(void);

#endif /* IRQHANDLER_H_ */
