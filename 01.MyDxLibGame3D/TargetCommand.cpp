//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̍U���ڕW�\���R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#include "TargetCommand.h"

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_CommandState TargetCommand::Execute()
{
    // ���ݑI�𒆂̃R�}���h�ł��邩�ǂ�����Ԃ�
    m_display = true;

    // �U���ڕW�̏�񂪓����Ă���Ƃ��łȂ��ƃZ�b�g�ł��Ȃ�
    if (Input::IsPress(ENTER) && m_obj != nullptr)
    {
        SetAttackObj(m_obj);
        return m_nextCommandType;
    }
    if (Input::IsPress(BACK))
    {
        return m_backCommandType;
    }
    return TAG_CommandState::TAG_None;
}

//-----------------------------------------------------------------------------
// @brief  �`�揈��.
//-----------------------------------------------------------------------------
void TargetCommand::Draw(int posY) const
{
    if (m_display)
    {
        DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowWhite), TRUE);
        if (m_obj != nullptr)
        {
            DrawFormatString(1480, posY + 10, GetColor(0, 0, 0), "%s", m_obj->GetName().c_str());
        }

        DrawArrowSide(1360, posY + 15);
        return;
    }
    DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowBlack), TRUE);
    if (m_obj != nullptr)
    {
        DrawFormatString(1480, posY + 10, GetColor(255, 255, 255), "%s", m_obj->GetName().c_str());
    }
}
