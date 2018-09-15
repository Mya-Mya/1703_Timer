#include"DxLib.h"

static int m_Key[256];  // �L�[�̓��͏�Ԋi�[�p�ϐ�
						// �L�[�̓��͏�ԍX�V
void Keyboard_Update() {
	char tmpKey[256];             // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey);  // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			m_Key[i]++;   // ���Z
		}
		else {              // ������Ă��Ȃ����
			m_Key[i] = 0; // 0�ɂ���
		}
	}
}
// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int Keyboard_Get(int KeyCode) {
	return m_Key[KeyCode]; // KeyCode�̓��͏�Ԃ�Ԃ�
}

typedef enum {
	scene_writing,//�J�E���g�b���̓��͒�
	scene_counting,//�J�E���g��
	scene_rumbling,//����
	scene_reset,//���Z�b�g
}hogehoge;

int int_counttime;//�J�E���g�b�����[
int int_Hzanalyzer;//60Hz��1�b�ϊ�

static int now = scene_writing;


void void_writing() {//�J�E���g�b���̓��͒�
	//�`��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�J�E���g����b������͂��Ă�\nEnter�ŃX�^�[�g�AEsc�Ń��Z�b�g");
	DrawFormatString(0, 100, GetColor(200, 200, 200), "%d �b", int_counttime);
	//�b�����͌v�Z
	if (int_counttime<1000) {//1000�b�ȓ�
		if (Keyboard_Get(KEY_INPUT_0) == 1) {
			int_counttime = (int_counttime * 10) + 0;//int_a�̍����̈ʂ�1�̐�����t������
		}
		if (Keyboard_Get(KEY_INPUT_1) == 1) {
			int_counttime = (int_counttime * 10) + 1;
		}
		if (Keyboard_Get(KEY_INPUT_2) == 1) {
			int_counttime = (int_counttime * 10) + 2;
		}
		if (Keyboard_Get(KEY_INPUT_3) == 1) {
			int_counttime = (int_counttime * 10) + 3;
		}
		if (Keyboard_Get(KEY_INPUT_4) == 1) {
			int_counttime = (int_counttime * 10) + 4;
		}
		if (Keyboard_Get(KEY_INPUT_5) == 1) {
			int_counttime = (int_counttime * 10) + 5;
		}
		if (Keyboard_Get(KEY_INPUT_6) == 1) {
			int_counttime = (int_counttime * 10) + 6;
		}
		if (Keyboard_Get(KEY_INPUT_7) == 1) {
			int_counttime = (int_counttime * 10) + 7;
		}
		if (Keyboard_Get(KEY_INPUT_8) == 1) {
			int_counttime = (int_counttime * 10) + 8;
		}
		if (Keyboard_Get(KEY_INPUT_9) == 1) {
			int_counttime = (int_counttime * 10) + 9;
		}
	}
	//Enter�ŃX�^�[�g
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {
		now = scene_counting;
	}
	//Esc�Ń��Z�b�g
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		now = scene_reset;
	}
}

void void_counting() {
	//�`��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�J�E���g�_�E�����ł��B\nEsc�Ń��Z�b�g");
	DrawFormatString(0, 100, GetColor(200, 200, 200), "�c��%d�b", int_counttime);
	//�v�Z 1�b=60Hz������int_counttime��--����
	if (int_Hzanalyzer == 60) {
		int_Hzanalyzer = 0;
		int_counttime--;
	}
	int_Hzanalyzer++;
	//Esc�Ń��Z�b�g
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		now = scene_reset;
	}
	//0�ɂȂ�����
	if (int_counttime==0) {
		now = scene_rumbling;
	}
}

void void_rumbling() {
	
	//����I�ɐF��ς��Ė�
	int_Hzanalyzer++;
	DrawFormatString(100, 200, GetColor(int_Hzanalyzer * 4, int_Hzanalyzer * 4, int_Hzanalyzer*4), "���Ԃł��BEsc�Ŏ~�߂�");
	if (int_Hzanalyzer == 60) {
		int_Hzanalyzer = 0;
	}
	//Esc�Ń��Z�b�g
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		now = scene_reset;
	}
}

void void_reset() {
	int_counttime = 0;
	now = scene_writing;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		Keyboard_Update();

		switch (now) {
		case scene_writing:
			void_writing();
			break;
		case scene_counting:
			void_counting();
			break;
		case scene_rumbling:
			void_rumbling();
			break;
		case scene_reset:
			void_reset();
			break;
		}

	}
	DxLib_End();
	return 0;
}