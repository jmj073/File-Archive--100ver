#define _CRT_SECURE_NO_WARNINGS    // fopen, strcpy ���� ���� ���� ������ ���� ����

#include "File_Archive_H.h"
#include <Windows.h>

int main() {
	int n, ret = 0;
	char bname[256];
	FILE* bfp = NULL;
	PARCHIVE Archive = (PARCHIVE)malloc(sizeof(ARCHIVE));

	if (Archive == NULL)
		return -1;

	printf("��ī�̺� ������ �̸��� �Է��� �ּ���\n�Է�:");
	scanf("%s", bname);

	while (1) {
		printf("�Ͻ� �۾��� ��ȣ�� �Է��� �ּ���\n");
		printf("1. ��ī�̺� ���Ͽ� ���� �߰� 2. ��ī�̺����� ��� ��� 0. ������\n�Է�:");
		scanf("%1d", &n);

		if (n == 0) {
			if (bfp == NULL)
				return 0;
			else
				goto exit1;
		}


		bfp = fopen(bname, "r+b");

		if (bfp == NULL) {
			if (n == 2)
				return -1;

			bfp = fopen(bname, "w+b");
			if (bfp == NULL) {
				ret = -1;
				goto exit2;//�ʹ� ��ħ!!!!!!!!!!!!!
			}

			Archive->header.magic = MG_NUM;
			Archive->header.version = AF_VER;

			if (fwrite(&Archive->header, sizeof(ARCHIVE_HEADER), 1, bfp) < 1) {
				printf("��ī�̺� ��� ���� ����");
				ret = -1;
				goto exit1;
			}

		}
		else {
			if (fread(&Archive->header, sizeof(ARCHIVE_HEADER), 1, bfp) < 1) {
				printf("��ī�̺� ���� ��� �б� ����\n");
				ret = -1;
				goto exit1;
			}

			if (Archive->header.magic != MG_NUM) {
				printf("��ī�̺� ������ ���� �ѹ��� �ƴմϴ�.");
				ret = -1;
				goto exit1;
			}
			if (Archive->header.version != AF_VER) {
				printf("������ ���� �ʽ��ϴ�.\n");
				ret = -1;
				goto exit1;
			}
		}

		Archive->fp = bfp;
		Archive->fileList = NULL;

		if (n == 1) {
			ret = append(Archive);
			if (ret == -1)
				goto exit1;
		}
		else if (n == 2) {
			ret = archive_print(Archive, bname);
			if (ret == -1)
				goto exit1;
			getchar();
			getchar();
		}
		system("cls");
	}

exit1:
	fclose(bfp);
exit2:
	free(Archive);
	
	return ret;
}