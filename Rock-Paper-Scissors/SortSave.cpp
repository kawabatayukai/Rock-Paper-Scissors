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
////更新
//void SortSave::Update()
//{
//
//}
//
////描画
//void SortSave::Draw()const
//{
//
//}
//
///*ランキング並べ替え*/
//void SortSave::SortRanking(void)
//{
//	int i, j;
//	RankingData work;
//
//	// 選択法ソート
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
//	// 順位付け
//	for (i = 0; i < RANKING_DATA; i++)
//	{
//		dataRanking[i].rank = 1;
//	}
//
//	// 得点が同じ場合は、同じ順位とする
//	// 同順位があった場合の次の順位はデータ個数が加算された順位とする
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
///*ランキングデータの保存*/
//int SortSave::SaveRanking(void)
//{
//	//FILE* fp;
////#pragma warning(disable:4996)
//
//	// ファイルオープン
//	if ((fopen_s(&fp, "dat/rankingdata.txt", "w")) != 0)
//	{
//		/* エラー処理 */
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	// ランキングデータ分配列データを書き込む
//	for (int i = 0; i < RANKING_DATA; i++)
//	{
//		fprintf_s(fp, "%2d %10s %10d\n", dataRanking[i].rank, dataRanking[i].name, dataRanking[i].score);
//	}
//
//	//ファイルクローズ
//	fclose(fp);
//
//	return 0;
//}
//
///*ランキングデータ読み込み*/
//int  SortSave::ReadRanking(void)
//{
//	//FILE* fp;
////#pragma warning(disable:4996)
//
//	//ファイルオープン
//	if ((fopen_s(&fp, "dat/rankingdata.txt", "r")) != 0)
//	{
//		//エラー処理
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	//ランキングデータ配分列データを読み込む
//	for (int i = 0; i < RANKING_DATA; i++)
//	{
//		fscanf_s(fp, "%2d %10s %10d", &dataRanking[i].rank, dataRanking[i].name, &dataRanking[i].score);
//	}
//
//	//ファイルクローズ
//	fclose(fp);
//
//	return 0;
//}
//
////シーンの変更処理
//AbstractScene* SortSave::ChangeScene()
//{
//	ReadRanking();
//	SortRanking();
//	SaveRanking();
//
//	return  dynamic_cast<AbstractScene*>(new Scene_Ranking(dataRanking));
//}
//
////スコアをセット
//void SortSave::setScore(int i, int score)
//{
//	if (0 <= score)
//	{
//		dataRanking[i].score = GameData::Get_Score();
//	}
//}