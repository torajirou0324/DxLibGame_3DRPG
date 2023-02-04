//-----------------------------------------------------------------------------
// @brief  タイトルシーンクラス.
//-----------------------------------------------------------------------------
#include "TitleScene.h"
#include "Field.h"
#include "Input.h"
#include "AssetManager.h"

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
TitleScene::TitleScene()
	: m_intervalNum(0)
	, m_addNum(0)
{
	// タイトルシーンに使うアセットをアセットマネージャーからもらう
	m_TitleHandle = AssetManager::UseImage(AssetManager::Title);
	m_arrowBesideHandle = AssetManager::UseImage(AssetManager::RightArrow);
	m_arrowVerticalHandle = AssetManager::UseImage(AssetManager::DownArrow);
	m_BlackWindow = AssetManager::UseImage(AssetManager::BlackWindow);
	m_arrowPosX = 500;
	m_arrowPosY = 640;
	m_playFlag = true;
	m_nameSettingFlag = false;
	m_playerHandle = AssetManager::UseModel(AssetManager::Player);
	int GraphHandle = AssetManager::UseImage(AssetManager::PlayerTexture1);
	int GraphHandle1 = AssetManager::UseImage(AssetManager::PlayerTexture2);
	int GraphHandle2 = AssetManager::UseImage(AssetManager::PlayerTexture3);
	int GraphHandle3 = AssetManager::UseImage(AssetManager::PlayerTexture4);
	MV1SetTextureGraphHandle(m_playerHandle, 0, GraphHandle, TRUE);
	MV1SetTextureGraphHandle(m_playerHandle, 1, GraphHandle2, TRUE);
	MV1SetTextureGraphHandle(m_playerHandle, 2, GraphHandle, TRUE);
	MV1SetTextureGraphHandle(m_playerHandle, 3, GraphHandle2, TRUE);
	MV1SetTextureGraphHandle(m_playerHandle, 4, GraphHandle, TRUE);
	MV1SetTextureGraphHandle(m_playerHandle, 5, GraphHandle1, TRUE);
	// プレイヤーモデルの大きさと座標をセット
	MV1SetScale(m_playerHandle, VGet(0.2f, 0.2f, 0.2f));
	MV1SetPosition(m_playerHandle, VGet(0.0f, 0.0f, 0.0f));

	// 向きに合わせてモデル回転
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(VGet(0.0f,0.0f,1.0f), rotYMat);

	// モデルに回転をセットする
	MV1SetRotationZYAxis(m_playerHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// モデルにAnimationをセット
	MV1DetachAnim(m_playerHandle, 0);
	auto attachIndex = MV1AttachAnim(m_playerHandle, 0, AssetManager::UseModel(AssetManager::AnimIdle));
	m_animTotalTime = MV1GetAnimTotalTime(AssetManager::UseModel(AssetManager::AnimIdle), attachIndex);
	m_animTime = 0.0f;

	// カメラのポジションと目標を初期化
	m_cameraPos = VGet(5.0f, 30.0f, 10.0f);
	m_targetPos = VGet(5.0f, 32.0f, 0.0f);
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
TitleScene::~TitleScene()
{
}

//-----------------------------------------------------------------------------
// @brief  更新処理.
//-----------------------------------------------------------------------------
TAG_SCENE TitleScene::Update()
{
	// カメラのポジションセット
	SetCameraPositionAndTarget_UpVecY(m_cameraPos, m_targetPos); // pos(0.0f, 60.0f, -50.0f) target(0.0f,20.0f,20.0f)

	// アニメーション繰り返し処理
	if (m_animTotalTime < m_animTime)
	{
		m_animTime = 0.0f;
	}

	// 現在のアニメーションフレームをモデルにアタッチする
	MV1SetAttachAnimTime(m_playerHandle, 0, m_animTime);

	// アニメーションフレーム加算
	m_animTime += 0.3f;

	if (Input::IsPress(LEFT))
	{
		m_arrowPosX = 150;
		m_playFlag = false;
	}
	if (Input::IsPress(RIGHT))
	{
		m_arrowPosX = 500;
		m_playFlag = true;
	}

	if (m_nameSettingFlag)
	{
		if (Input::IsPress(ENTER))
		{
			return TAG_SCENE::TAG_PLAY;
		}
	}

	if (m_playFlag && Input::IsPress(ENTER))
	{
		m_nameSettingFlag = true;
		m_arrowPosX = 980;
		m_arrowPosY = 920;
		SetFontSize(35);
	}

	if (!m_playFlag && Input::IsPress(ENTER))
	{
		return TAG_SCENE::TAG_ESCAPE;
	}

	m_intervalNum++;
	if (m_intervalNum > 7)
	{
		m_intervalNum = 0;
		m_addNum++;
		if (m_addNum > 20)
		{
			m_addNum = 0;
		}
	}

	return TAG_SCENE::TAG_NONE;
}

//-----------------------------------------------------------------------------
// @brief  描画処理.
//-----------------------------------------------------------------------------
void TitleScene::Draw()
{
	//printfDx("TitleScene\n");
	Field::DrawCall();
	MV1DrawModel(m_playerHandle);
	DrawGraph(100, 420, m_TitleHandle, TRUE);
	if (!m_nameSettingFlag)
	{
		DrawFormatString(250, 630, GetColor(255, 255, 255), "おわる");
		DrawFormatString(600, 630, GetColor(255, 255, 255), "はじめる");

		DrawGraph(m_arrowPosX + m_addNum, m_arrowPosY, m_arrowBesideHandle, TRUE);
	}
	else
	{
		DrawExtendGraph(100, 700, 1060, 1000, m_BlackWindow, TRUE);
		DrawFormatString(150, 760, GetColor(255, 255, 255), "あなたは キツキ イチカ \n3面＋ボス部屋があるダンジョン\nスキルを使いモンスターを倒して成長し\nボスをたおすとゲームクリア");
		DrawGraph(m_arrowPosX, m_arrowPosY + m_addNum, m_arrowVerticalHandle, TRUE);
	}

}
