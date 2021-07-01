#define _CRT_SECURE_NO_WARNINGS    // fopen, strcpy 보안 경고로 인한 컴파일 에러 방지

#ifndef FILE_ARCHIVE_H
#define FILE_ARCHIVE_H

#include <stdio.h>     // 파일 처리 함수가 선언된 헤더 파일
#include <stdint.h>    // 크기별로 정수 자료형이 정의된 헤더 파일
#include <stdlib.h>    // malloc, free 함수가 선언된 헤더 파일
#include <string.h>    // strcpy, memset 함수가 선언된 헤더 파일

#define MG_NUM 'AF'
#define AF_VER 1


#pragma pack(push, 1)

// 아카이브 파일에 저장되는 구조체
typedef struct _ARCHIVE_HEADER {   // 아카이브 헤더 구조체 정의
    uint16_t magic;                    // 아카이브 파일 매직 넘버
    uint16_t version;                  // 아카이브 파일 버전
} ARCHIVE_HEADER, * PARCHIVE_HEADER;

// 아카이브 파일에 저장되는 구조체
typedef struct _FILE_DESC {    // 파일 정보 구조체 정의
    char     name[256];            // 파일 이름
    uint32_t size;                 // 파일 크기
    uint32_t dataOffset;           // 파일 데이터의 위치
} FILE_DESC, * PFILE_DESC;

#pragma pack(pop)

// 프로그램에서만 사용하는 구조체
typedef struct _FILE_NODE {    // 파일 목록 연결 리스트 구조체 정의
    struct _FILE_NODE* next;       // 다음 노드의 주소를 저장할 포인터
    FILE_DESC desc;                // 파일 정보
} FILE_NODE, * PFILE_NODE;

// 프로그램에서만 사용하는 구조체
typedef struct _ARCHIVE {    // 아카이브 메인 구조체
    ARCHIVE_HEADER header;       // 아카이브 헤더
    FILE* fp;                    // 아카이브 파일 포인터
    PFILE_NODE fileList;          // 파일 목록 연결 리스트의 머리 노드
} ARCHIVE, * PARCHIVE;


uint32_t getFileSize(FILE* fp);

int append(PARCHIVE Archive);
int archive_print(PARCHIVE Archive, char bname[]);
void Print_List(PFILE_NODE Node);

#endif