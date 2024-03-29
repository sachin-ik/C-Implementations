#include<stdio.h>
#include<stdlib.h>

const int i = 1;
#define is_bigendian() ((*((char*)(&i))) == 0)
#define my_sizeof(type) ((char*)(&type+1) - (char*)(&type))

#define get_bits(num, start_bit, width) ((num >> start_bit) & ((1<<width)-1))
// int get_bits(int num, int start_bit, int width){
//     int mask = (1<<width)-1;
//     return ((num>>start_bit) & mask);
// } 

int clear_bits(int num, int n){
    //first n bits cleared here from msb
    return num & ((1<<(32-n))-1);
}

int clear_bits_lsb(int num, int n){
    //ex: num = 0x1234 n = 2
    // 0x1234567 & ~((1 << 2)-1)
    // 0x1234567 & ~(0b11)
    // 0x1234567 & 0b111111....00
    // 0x1234564 // last 2 bits cleared
    return num & ~((1<<(n))-1);
}

int sys_byte_size(void)
{
    long a = 0;
    return (char*)(&a+1) - (char*)(&a);
}

void set_bit(unsigned int* num, int bit)
{
    (*num) |= (1 << bit);
}

void clear_bit(unsigned int* num, int bit)
{
    (*num) &= ~(1 << bit);
}

void toggle_bit(unsigned int* num, int bit)
{
    (*num) ^= (1 << bit);
}

int get_bit(unsigned int num, int bit)
{
    return (num >> bit) & 1;
}

void print_binary(unsigned int num)
{
    int i;
    printf("0b");
    for(i = 31; i >= 0; i--)
    {
        printf("%d",get_bit(num,i));
    }
    printf("\n");
}

void print_hex(unsigned int num)
{
    printf("0x%x\n",num);
}   

int count_set_bits(unsigned int num)
{
    int count = 0;
    // 6 = 0b110
    // 5 = 0b101 -> (6 & 5) = 0b100 = 4
    // 4 = 0b100 -> (4 & 3) = 0b000 = 0
    //uses only the number of set bits iterations
    while(num){
        num = num & (num-1);
        count++;
    }
    return count;
}

int count_set_bits2(unsigned int num)
{
    int count = 0;
    //6 = 0b110
    // count += 6 & 1 = 0
    // num >>= 1 = 0b11
    // count += 3 & 1 = 1
    // num >>= 1 = 0b1
    // count += 1 & 1 = 1
    //uses all the bits iterations
    while(num)
    {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

void swap(int* a, int* b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;   // *b = *a ^ *b ^ *b = *a
    *a = *a ^ *b;   // *a = *a ^ *b ^ *a = *b
}

void swap2(int* a, int* b)
{
    *a = *a + *b;
    *b = *a - *b;   // *b = *a + *b - *b = *a
    *a = *a - *b;   // *a = *a + *b - *a = *b
}

void reverse_bits(unsigned int* num)
{
    int i;
    unsigned int result = 0;
    for(i=0; i<32; i++)
    {
        result <<= 1;
        result |= (*num & 1);
        *num >>= 1;
    }
    *num = result;
}

//reverse bits in optimized way
void reverse_bits2(unsigned int* num)
{
    unsigned int a = (*num & 0x55555555) << 1;
    unsigned int b = (*num & 0xaaaaaaaa) >> 1;
    *num = a | b;
    a = (*num & 0x33333333) << 2;
    b = (*num & 0xcccccccc) >> 2;
    *num = a | b;
    a = (*num & 0x0f0f0f0f) << 4;
    b = (*num & 0xf0f0f0f0) >> 4;
    *num = a | b;
    a = (*num & 0x00ff00ff) << 8;
    b = (*num & 0xff00ff00) >> 8;
    *num = a | b;
    a = (*num & 0x0000ffff) << 16;
    b = (*num & 0xffff0000) >> 16;
    *num = a | b;
}

//reverse bits in optimized way
void reverse_bits3(unsigned int* num)
{
    // *num = (*num & 0x55555555) << 1 | (*num & 0xaaaaaaaa) >> 1;
    // *num = (*num & 0x33333333) << 2 | (*num & 0xcccccccc) >> 2;
    // *num = (*num & 0x0f0f0f0f) << 4 | (*num & 0xf0f0f0f0) >> 4;
    // *num = (*num & 0x00ff00ff) << 8 | (*num & 0xff00ff00) >> 8;
    // *num = (*num & 0x0000ffff) << 16 | (*num & 0xffff0000) >> 16;

    *num = (*num & 0x55555555) << 1 | (*num & 0xaaaaaaaa) >> 1;
    *num = (*num & 0x33333333) << 2 | (*num & 0xcccccccc) >> 2;
    *num = (*num & 0x0f0f0f0f) << 4 | (*num & 0xf0f0f0f0) >> 4;
    *num = (*num & 0x00ff00ff) << 8 | (*num & 0xff00ff00) >> 8;
    *num = (*num & 0x0000ffff) << 16 | (*num & 0xffff0000) >> 16;
}

int main()
{
    if(is_bigendian())
    {
        printf("Big endian\n");
    }
    else
    {
        printf("Little endian\n");
    }
    printf("System byte size: %d\n",sys_byte_size());
    int a = 10;
    char b = 'a';
    float c = 10.5;
    double d = 10.5;
    long e = 10;
    short int f = 10;    
    printf("my_sizeof(char): %d\n",my_sizeof(b));
    printf("my_sizeof(short int): %d\n",my_sizeof(f));
    printf("my_sizeof(int): %d\n",my_sizeof(a));
    printf("my_sizeof(long): %d\n",my_sizeof(e));
    printf("my_sizeof(float): %d\n",my_sizeof(c));
    printf("my_sizeof(double): %d\n",my_sizeof(d));

    unsigned int num = 0x12345678;
    print_binary(num);
    int g = get_bits(num, 6, 4);
    printf("get bits from start_idx with width: 0x%x\n", g);
    printf("clear bits from msb: 0x%x\n", clear_bits(num, 2));
    num = 0x0000ffff;
    print_binary(num);
    printf("Before reverse: \n");
    print_hex(num);
    reverse_bits3(&num);
    printf("After reverse: \n");
    print_hex(num);

    printf("count set bits : %d\n", count_set_bits(num));
    
    int x = 10;
    int y = 20;
    printf("Before swap x: %d, y: %d\n",x,y);
    swap(&x, &y);
    printf("After swap x: %d, y: %d\n",x,y);
    
    
    return 0;
} 