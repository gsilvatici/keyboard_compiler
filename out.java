import java.util.Scanner;
public class out {

 public static void test1() { 
 System.out.print("Hello world!\n");
 }

 public static void test2() { 
 String hello = " ";
 hello = "Im saying hello world again!";
 System.out.print(hello); 
 System.out.print("\n"); 
 Integer number = 8 + 2; 
 number = number - (4 * 2);
 System.out.print("El numero 2 es\n");
 System.out.print(number); 
 System.out.print("\n"); 
 }

 public static void test3() { 
 Integer number1 = 5; 
 Integer number2 = 5; 
 Integer number3 = 2; 
 if ( number1 == number2 ) { 
 System.out.print("5 igual a 5\n");
 Integer numb9 = 9; 
 }
 if ( number3 > number2 ) { 
 System.out.print("2 mayor que 5\n");
 }
 if ( ! ( number3 > number2 ) ) { 
 System.out.print("2 no es mayor que 5\n");
 }
 }

 public static void test4() { 
 System.out.print("contemos de 0 a 10\n");
 for ( int number = 0 ; number <= 10 ; number++ ) { 
 System.out.print(number); 
 System.out.print("\n"); 
 }
 Integer number3 = 3; 
 Integer number2 = 5; 
 System.out.print("contemos de 0 a 5\n");
 for ( number3 = 0 ; number3 <= number2 ; number3++ ) { 
 System.out.print(number3); 
 System.out.print("\n"); 
 }
 }

 public static void test5() { 
 Integer number = 1; 
 while ( number < 10 ) { 
 number = number + 1;
 String unstring = "unstring";
 }
 System.out.print(" numero 10\n");
 System.out.print(number); 
 System.out.print("\n"); 
 }

 public static void main(String[] args) { 
 System.out.print("test 1\n");
 test1();
 System.out.print("test 2\n");
 test2();
 System.out.print("test 3\n");
 test3();
 System.out.print("test 4\n");
 test4();
 System.out.print("test 5\n");
 test5();
 }

}
