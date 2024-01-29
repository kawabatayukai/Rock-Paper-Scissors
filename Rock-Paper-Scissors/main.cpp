#include"DxLib.h"
#include"SceneManager.h"
#include"Scene_GameMain.h"
#include"Scene_Title.h"
#include"Jangeki_Player.h"
#include"SoundSystem.h"
#include "Scne_TitleInterval.h"
#include"KeyManager.h"
#include"FPS_Controll.h"

/*�@�@�ϐ��@�@*/
int g_OldKey;      // �O��̓��̓L�[ 
int g_NowKey;      // ����̓��̓L�[ 
int g_KeyFlg;      // ���̓L�[���


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
    SetMainWindowText("JANKEN WORLD");       //�^�C�g����ݒ�
    ChangeWindowMode(TRUE);                //�E�B���h�E���[�h�ŋN��
    //SetWindowSize(1280, 720);
    SetGraphMode(1280, 720, 32);           //�E�B���h�E�T�C�Y��ݒ�
    SetWindowIconID(123);                  //�E�B���h�E�̃A�C�R��
    if (DxLib_Init() == -1) return -1;     //DX���C�u�����̏���������
    SetDrawScreen(DX_SCREEN_BACK);         //�`����ʂ𗠂ɂ���

    //�V�[���}�l�[�W���[     �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�^�C�g����ݒ�
    SceneManager sceneMng(dynamic_cast<AbstractScene*>(new Scne_TitleInterval()));

    //����񌂉摜
    Jangeki_Player::LoadJanImage();
    Jangeki_Base::Input_Images();

    //�T�E���h
    SoundSystem::LoadSounds_SE();
    //SoundSystem::LoadSounds_BGM();

    //FPS�Œ�p
    FPS_Controll fps_ctrl(60);

    //ESC�L�[�܂��̓R���g���[���[Back�{�^���ŏI��
    while (ProcessMessage() == 0 && !KeyManager::OnKeyClicked(KEY_INPUT_ESCAPE) && !KeyManager::OnPadClicked(PAD_INPUT_7))
    {
        // ��ʂ̏����� 
        ClearDrawScreen();

        sceneMng.Update();     //�X�V
        sceneMng.Draw();       //�`��

        //�V�[���̕ύX   END�̏ꍇ�@nullptr
        if (sceneMng.ChangeScene() == nullptr)
        {
            DxLib_End();  //DxLib�I������
            return 0;
        }

        //FPS�Œ菈��
        fps_ctrl.Get();
        fps_ctrl.Wait();
        //fps_ctrl.Disp();
        //DrawFormatString(0, 50, 0xff0000, "%f", GetFPS());

        //����ʂ̓��e��\��ʂɔ��f
        ScreenFlip();
    }

    DxLib_End();		    // �c�w���C�u�����g�p�̏I������

    return 0;				// �\�t�g�̏I�� 
}