/*************************************************
*�Ԕ����Q�[��������Ă݂悤
**************************************************/
#include "DxLib.h"
#include"Scene/SceneManager.h"

//���C���֐�(�v���O�����͂�������n�܂�܂��B�j
int WINAPI WinMain(_In_HINSTANCE hInstance, _In_opt_HINSTANCE hPrevInstance,
	_In_LPSTR lpCmdLine, _In_int nCmdShow)
{
	//��O�����i�ُ킪����������Acatch���ɔ�т܂�
	try
	{
		//�V�[���}�l�[�W���[�@�\�̐���
		SceneManager manager;
		//�V�[���}�l�[�W���[�@�\�̏���������
		manager.Initialize();
		//�V�[���}�l�[�W���[�@�\�̍X�V����
		manager.Update();
		//�V�[���}�l�[�W���[�@�\�̏I��������
		manager.Finslize();
	}
	catch (const char* err_log)
	{
		//�G���[�������e�̏o��
		OutputDebugString(err_log);

		//�G���[�I����ʒm
		return -1;
	}
	//����I����ʒm
	return 0;
}