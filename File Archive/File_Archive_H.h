#define _CRT_SECURE_NO_WARNINGS    // fopen, strcpy ���� ���� ���� ������ ���� ����

#ifndef FILE_ARCHIVE_H
#define FILE_ARCHIVE_H

#include <stdio.h>     // ���� ó�� �Լ��� ����� ��� ����
#include <stdint.h>    // ũ�⺰�� ���� �ڷ����� ���ǵ� ��� ����
#include <stdlib.h>    // malloc, free �Լ��� ����� ��� ����
#include <string.h>    // strcpy, memset �Լ��� ����� ��� ����

#define MG_NUM 'AF'
#define AF_VER 1


#pragma pack(push, 1)

// ��ī�̺� ���Ͽ� ����Ǵ� ����ü
typedef struct _ARCHIVE_HEADER {   // ��ī�̺� ��� ����ü ����
    uint16_t magic;                    // ��ī�̺� ���� ���� �ѹ�
    uint16_t version;                  // ��ī�̺� ���� ����
} ARCHIVE_HEADER, * PARCHIVE_HEADER;

// ��ī�̺� ���Ͽ� ����Ǵ� ����ü
typedef struct _FILE_DESC {    // ���� ���� ����ü ����
    char     name[256];            // ���� �̸�
    uint32_t size;                 // ���� ũ��
    uint32_t dataOffset;           // ���� �������� ��ġ
} FILE_DESC, * PFILE_DESC;

#pragma pack(pop)

// ���α׷������� ����ϴ� ����ü
typedef struct _FILE_NODE {    // ���� ��� ���� ����Ʈ ����ü ����
    struct _FILE_NODE* next;       // ���� ����� �ּҸ� ������ ������
    FILE_DESC desc;                // ���� ����
} FILE_NODE, * PFILE_NODE;

// ���α׷������� ����ϴ� ����ü
typedef struct _ARCHIVE {    // ��ī�̺� ���� ����ü
    ARCHIVE_HEADER header;       // ��ī�̺� ���
    FILE* fp;                    // ��ī�̺� ���� ������
    PFILE_NODE fileList;          // ���� ��� ���� ����Ʈ�� �Ӹ� ���
} ARCHIVE, * PARCHIVE;


uint32_t getFileSize(FILE* fp);

int append(PARCHIVE Archive);
int archive_print(PARCHIVE Archive, char bname[]);
void Print_List(PFILE_NODE Node);

#endif