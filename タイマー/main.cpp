#include"DxLib.h"

static int m_Key[256];  // キーの入力状態格納用変数
						// キーの入力状態更新
void Keyboard_Update() {
	char tmpKey[256];             // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey);  // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			m_Key[i]++;   // 加算
		}
		else {              // 押されていなければ
			m_Key[i] = 0; // 0にする
		}
	}
}
// KeyCodeのキーの入力状態を取得する
int Keyboard_Get(int KeyCode) {
	return m_Key[KeyCode]; // KeyCodeの入力状態を返す
}

typedef enum {
	scene_writing,//カウント秒数の入力中
	scene_counting,//カウント中
	scene_rumbling,//鳴動中
	scene_reset,//リセット
}hogehoge;

int int_counttime;//カウント秒数収納
int int_Hzanalyzer;//60Hzと1秒変換

static int now = scene_writing;


void void_writing() {//カウント秒数の入力中
	//描画
	DrawFormatString(0, 0, GetColor(255, 255, 255), "カウントする秒数を入力してね\nEnterでスタート、Escでリセット");
	DrawFormatString(0, 100, GetColor(200, 200, 200), "%d 秒", int_counttime);
	//秒数入力計算
	if (int_counttime<1000) {//1000秒以内
		if (Keyboard_Get(KEY_INPUT_0) == 1) {
			int_counttime = (int_counttime * 10) + 0;//int_aの左側の位に1の数字を付け足す
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
	//Enterでスタート
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {
		now = scene_counting;
	}
	//Escでリセット
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		now = scene_reset;
	}
}

void void_counting() {
	//描画
	DrawFormatString(0, 0, GetColor(255, 255, 255), "カウントダウン中です。\nEscでリセット");
	DrawFormatString(0, 100, GetColor(200, 200, 200), "残り%d秒", int_counttime);
	//計算 1秒=60Hz周期でint_counttimeを--する
	if (int_Hzanalyzer == 60) {
		int_Hzanalyzer = 0;
		int_counttime--;
	}
	int_Hzanalyzer++;
	//Escでリセット
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1) {
		now = scene_reset;
	}
	//0になったら
	if (int_counttime==0) {
		now = scene_rumbling;
	}
}

void void_rumbling() {
	
	//定期的に色を変えて鳴動
	int_Hzanalyzer++;
	DrawFormatString(100, 200, GetColor(int_Hzanalyzer * 4, int_Hzanalyzer * 4, int_Hzanalyzer*4), "時間です。Escで止める");
	if (int_Hzanalyzer == 60) {
		int_Hzanalyzer = 0;
	}
	//Escでリセット
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