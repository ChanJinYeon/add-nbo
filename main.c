#include <stdio.h>
#include <stdint.h>

// big endian -> little endian
uint32_t my_ntohl(uint32_t n) {
        return (n >> 24 ) + (n << 24)
                + ((n << 8) & 0x00FF0000)
                + ((n >> 8) & 0x0000FF00);
}

int main(int argc, char* argv[])
{
    // read
    FILE *f1, *f2;
    f1 = fopen(argv[1], "rb");
    f2 = fopen(argv[2], "rb");

    // 예외 처리
    if (f1 == NULL || f2 == NULL) {
        puts("파일 읽기 실패\n");
        fclose(f1);
        fclose(f2);
        return 1;
    }

    // 예외 처리
    fseek(f1, 0, SEEK_END);
    fseek(f2, 0, SEEK_END);
    int f1_len = ftell(f1);
    int f2_len = ftell(f2);
    fseek(f1, 0, SEEK_SET);
    fseek(f2, 0, SEEK_SET);

    if (f1_len != 4 || f2_len != 4) {
        puts("파일이 4 bytes가 아닙니다\n");
        fclose(f1);
        fclose(f2);
        return 1;
    }


    // 값 저장
    uint32_t n1, n2;
    fread(&n1, sizeof(uint32_t), 1, f1);
    fread(&n2, sizeof(uint32_t), 1, f2);

    fclose(f1);
    fclose(f2);


    // 엔디안 변환
    n1 = my_ntohl(n1);
    n2 = my_ntohl(n2);

    // 계산
    uint32_t result = n1 + n2;    

    // 결과
    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", n1, n1, n2, n2, result, result);

    return 0;
}
