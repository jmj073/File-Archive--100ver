#define _CRT_SECURE_NO_WARNINGS    // fopen, strcpy 보안 경고로 인한 컴파일 에러 방지

#include "File_Archive_H.h"
#include <Windows.h>

int main() {
	int n, ret = 0;
	char bname[256];
	FILE* bfp = NULL;
	PARCHIVE Archive = (PARCHIVE)malloc(sizeof(ARCHIVE));

	if (Archive == NULL)
		return -1;

	printf("아카이브 파일의 이름을 입력해 주세요\n입력:");
	scanf("%s", bname);

	while (1) {
		printf("하실 작업의 번호를 입력해 주세요\n");
		printf("1. 아카이브 파일에 파일 추가 2. 아카이브파일 목록 출력 0. 끝내기\n입력:");
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
				goto exit2;//너무 겹침!!!!!!!!!!!!!
			}

			Archive->header.magic = MG_NUM;
			Archive->header.version = AF_VER;

			if (fwrite(&Archive->header, sizeof(ARCHIVE_HEADER), 1, bfp) < 1) {
				printf("아카이브 헤더 쓰기 실패");
				ret = -1;
				goto exit1;
			}

		}
		else {
			if (fread(&Archive->header, sizeof(ARCHIVE_HEADER), 1, bfp) < 1) {
				printf("아카이브 파일 헤더 읽기 실패\n");
				ret = -1;
				goto exit1;
			}

			if (Archive->header.magic != MG_NUM) {
				printf("아카이브 파일의 매직 넘버가 아닙니다.");
				ret = -1;
				goto exit1;
			}
			if (Archive->header.version != AF_VER) {
				printf("버전이 맞지 않습니다.\n");
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