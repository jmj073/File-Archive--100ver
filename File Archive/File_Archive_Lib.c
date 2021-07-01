#define _CRT_SECURE_NO_WARNINGS    // fopen, strcpy ���� ���� ���� ������ ���� ����
#include "File_Archive_H.h"

uint32_t getFileSize(FILE* fp) {
	int size = 0;
	int currPos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, currPos, SEEK_SET);

	return size;
}

int append(PARCHIVE Archive) {
	int ret = 0;
	char fname[256] = { 0 };

	printf("�߰��� ������ �̸��� �Է��� �ּ���\n�Է�:");
	scanf("%s", fname);

	FILE* fp = fopen(fname, "rb");
	if (fp == NULL) {
		printf("���� �����Դϴ�!");
		return -1;
	}

	uint8_t* buffer = NULL;
	uint32_t size;

	size = getFileSize(fp);
	buffer = (uint8_t*)malloc(size);
	if (buffer == NULL) {
		ret = -1;
		goto exit1;
	}

	if (fread(buffer, size, 1, fp) < 1) {
		ret = -1;
		goto exit2;
	}

	PFILE_DESC desc = (PFILE_DESC)malloc(sizeof(FILE_DESC));
	if (desc == NULL) {
		ret = -1;
		goto exit2;
	}
	memset(desc, 0, sizeof(FILE_DESC));
	strcpy(desc->name, fname);
	desc->size = size;

	fseek(Archive->fp, 0, SEEK_END);
	desc->dataOffset = ftell(Archive->fp) + sizeof(FILE_DESC);

	if (fwrite(desc, sizeof(FILE_DESC), 1, Archive->fp) < 1) {
		printf("���� ���� ���� ����\n");
		ret = -1;
		goto exit2;
	}

	if (fwrite(buffer, size, 1, Archive->fp) < 1) {
		printf("���� ������ ���� ����\n");
		ret = -1;
		goto exit2;
	}

	printf("%s ���� �߰� ����\nũ��: %d\n", fname, size);


exit2:
	free(buffer);
exit1:
	fclose(fp);

	return ret;
}

int archive_print(PARCHIVE Archive, char bname[]) {
	int ret = 0;
	PFILE_NODE Curr = NULL, FList = Archive->fileList;
	FILE* fp = Archive->fp;
	uint32_t size = getFileSize(fp);
	uint32_t currPos = ftell(fp);

	while (size > currPos) {
		PFILE_NODE Node = (PFILE_NODE)malloc(sizeof(FILE_NODE));
		if (Node == NULL)
			return -1;
		memset(Node, 0, sizeof(FILE_NODE));

		if (fread(&Node->desc, sizeof(FILE_DESC), 1, fp) < 1) {
			printf("��ī�̺� ���� �б� ����!\n");
			goto Finalize;
		}
		currPos = Node->desc.dataOffset + Node->desc.size;
		fseek(fp, currPos, SEEK_SET);

		if (FList == NULL)
			FList = Node;
		else
			Curr->next = Node;

		Curr = Node;
	}

	Print_List(FList);

Finalize:

	Curr = FList;
	while (FList != NULL) {
		FList = FList->next;
		free(Curr);
		Curr = FList;
	}

	return ret;
}

void Print_List(PFILE_NODE Node) {
	printf("���� ���:\n");

	while (Node != NULL) {
		printf("���� �̸�:%s, ���� ũ��:%d\n", Node->desc.name, Node->desc.size);
		Node = Node->next;
	}
}