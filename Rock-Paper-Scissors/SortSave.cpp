//#include "SortSave.h"
//#include "GameData.h"
//#include"Scene_Ranking.h"
//
//SortSave::SortSave(const char* name)
//{
//	for (int i = 0; i < RANKING_DATA; i++)
//	{
//		for (int j = 0; dataRanking[i].name[j] != '\0'; j++)
//		{
//			dataRanking[i].name[j] = name[j];
//		}
//		dataRanking[i].rank = 0;
//		dataRanking[i].score = 0;
//	}
//}
//
////�X�V
//void SortSave::Update()
//{
//
//}
//
////�`��
//void SortSave::Draw()const
//{
//
//}
//
///*�����L���O���בւ�*/
//void SortSave::SortRanking(void)
//{
//	int i, j;
//	RankingData work;
//
//	// �I��@�\�[�g
//	for (i = 0; i < 9; i++) {
//		for (j = i + 1; j < RANKING_DATA; j++) {
//			if (dataRanking[i].score <= dataRanking[j].score)
//			{
//				work = dataRanking[i];
//				dataRanking[i] = dataRanking[j];
//				dataRanking[j] = work;
//			}
//		}
//	}
//
//	// ���ʕt��
//	for (i = 0; i < RANKING_DATA; i++)
//	{
//		dataRanking[i].rank = 1;
//	}
//
//	// ���_�������ꍇ�́A�������ʂƂ���
//	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
//	for (i = 0; i < RANKING_DATA - 1; i++) {
//		for (j = i + 1; j < RANKING_DATA; j++) {
//			if (dataRanking[i].score > dataRanking[j].score)
//			{
//				dataRanking[j].rank++;
//			}
//		}
//	}
//}
//
///*�����L���O�f�[�^�̕ۑ�*/
//int SortSave::SaveRanking(void)
//{
//	//FILE* fp;
////#pragma warning(disable:4996)
//
//	// �t�@�C���I�[�v��
//	if ((fopen_s(&fp, "dat/rankingdata.txt", "w")) != 0)
//	{
//		/* �G���[���� */
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	// �����L���O�f�[�^���z��f�[�^����������
//	for (int i = 0; i < RANKING_DATA; i++)
//	{
//		fprintf_s(fp, "%2d %10s %10d\n", dataRanking[i].rank, dataRanking[i].name, dataRanking[i].score);
//	}
//
//	//�t�@�C���N���[�Y
//	fclose(fp);
//
//	return 0;
//}
//
///*�����L���O�f�[�^�ǂݍ���*/
//int  SortSave::ReadRanking(void)
//{
//	//FILE* fp;
////#pragma warning(disable:4996)
//
//	//�t�@�C���I�[�v��
//	if ((fopen_s(&fp, "dat/rankingdata.txt", "r")) != 0)
//	{
//		//�G���[����
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	//�����L���O�f�[�^�z����f�[�^��ǂݍ���
//	for (int i = 0; i < RANKING_DATA; i++)
//	{
//		fscanf_s(fp, "%2d %10s %10d", &dataRanking[i].rank, dataRanking[i].name, &dataRanking[i].score);
//	}
//
//	//�t�@�C���N���[�Y
//	fclose(fp);
//
//	return 0;
//}
//
////�V�[���̕ύX����
//AbstractScene* SortSave::ChangeScene()
//{
//	ReadRanking();
//	SortRanking();
//	SaveRanking();
//
//	return  dynamic_cast<AbstractScene*>(new Scene_Ranking(dataRanking));
//}
//
////�X�R�A���Z�b�g
//void SortSave::setScore(int i, int score)
//{
//	if (0 <= score)
//	{
//		dataRanking[i].score = GameData::Get_Score();
//	}
//}