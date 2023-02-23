//-----------------------------------------------------------------------------
// @brief  �o�g���C�x���g�̋Z�\���R�}���h�I�������N���X.
//-----------------------------------------------------------------------------
#include "SkillCommand.h"

//-----------------------------------------------------------------------------
// @brief  �X�V����.
//-----------------------------------------------------------------------------
TAG_CommandState SkillCommand::Execute()
{
    // ���ݑI�𒆂̃R�}���h�ł��邩�ǂ�����Ԃ�
    m_display = true;

    if (Input::IsPress(ENTER))
    {
        SetPlayerSkill(m_skill);
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
void SkillCommand::Draw(int posY) const
{
    if (m_display)
    {
        DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowWhite), TRUE);
        DrawFormatString(1480, posY + 10, GetColor(0, 0, 0), "%s", m_skill.SkillName.c_str());

        DrawArrowSide(1360, posY + 15);
        return;
    }
    DrawGraph(1400, posY, AssetManager::UseImage(AssetManager::CommandWindowBlack), TRUE);
    DrawFormatString(1480, posY + 10, GetColor(255, 255, 255), "%s", m_skill.SkillName.c_str());
}
