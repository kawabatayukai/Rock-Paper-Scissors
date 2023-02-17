#include "SceneManager.h"
#include"KeyManager.h"

//�X�V
void SceneManager::Update()
{
    //���݃V�[���̃A�b�v�f�[�g�����s
    mScene->Update();

    //�L�[�{�[�h�̃A�b�v�f�[�g�����s
    KeyManager::Update();
}


//���݂̃V�[���� Draw(�`����s���֐�)�݂̂����s
void SceneManager::Draw() const
{
    //const �̓����o�ϐ��̕ύX������
    mScene->Draw();
}

//�V�[���̕ύX����
AbstractScene* SceneManager::ChangeScene()
{
    //���݂̃V�[���̃V�[���ύX�����s
    AbstractScene* NextScene = mScene->ChangeScene();

    //���̃V�[�������݂̃V�[���ƈقȂ�ꍇ�A���̃V�[���ɐ؂�ւ���
    if (NextScene != mScene)
    {
        delete mScene;        //���݂̃V�[�����폜
        mScene = NextScene;   //���̃V�[���ɐ؂�ւ���
    }

    //�V���ȃV�[����Ԃ�
    return NextScene;
}