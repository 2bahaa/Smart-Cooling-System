/*
 * BIT_MATH.h
 *
 * Created: 5/27/2024 10:42:58 PM
 *  Author: Mohamed Bahaa
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define Set_Bit(REG,BIT) (REG |= (1<<BIT))      
#define Clear_Bit(REG,BIT) (REG &= (~(1<<BIT)))
#define Toggle_Bit(REG,BIT) (REG ^= (1<<BIT))



#endif /* BIT_MATH_H_ */