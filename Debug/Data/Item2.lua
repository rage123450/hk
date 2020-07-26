dofile 'DataEnum.lua'

g_pItemManager:AddItemTemplet({
  m_ItemID = 30012,
  m_Name = "(old)Ancient Warrior's Blade",
  m_Description = [[
The strongest warriors among the Lizard men
 use such strong knives.]],
  m_ModelName = "Mesh_Raven_Elite_Weapon_30012_Sorted.X",
  m_UseType = USE_TYPE.UT_ATTACH_ANIM,
  m_AttachFrameName = "Dummy1_Rhand",
  m_ShopImage = "HQ_Shop_Raven_Elite_Weapon_30012.dds",
  m_DropViewer = "DropItemDrop_Weapon_Raven",
  m_UseCondition = USE_CONDITION.UC_ONE_UNIT,
  m_UnitType = UNIT_TYPE.UT_RAVEN,
  m_UnitClass = UNIT_CLASS.UC_RAVEN_FIGHTER,
  m_UseLevel = 22,
  m_ItemLevel = 38,
  m_ItemType = ITEM_TYPE.IT_WEAPON,
  m_ItemGrade = ITEM_GRADE.IG_ELITE,
  m_bVested = True,
  m_bCanEnchant = True,
  m_ucMaxSealCount = 5,
  m_iMaxAttribEnchantCount = 2,
  m_PeriodType = PERIOD_TYPE.PT_ENDURANCE,
  m_Endurance = 10000,
  m_EnduranceDamageMin = 50,
  m_EnduranceDamageMax = 70,
  m_RepairED = 6.6,
  m_Price = 93600,
  m_EqipPosition = EQIP_POSITION.EP_WEAPON_HAND,
  m_Stat = { m_fAtkPhysic = 1621, m_fAtkMagic = 1432},
  SOCKET_OPTION = {
    1603,
    1505,
    1703,
    1903
  }
})
g_pItemManager:AddItemTemplet({
  m_ItemID = 30013,
  m_Name = "(old)Scorpion Armour",
  m_Description = "Scorpions from the Besma region have incredibly beautiful shells.",
  m_ModelName = "Mesh_Common_Elite_LOWBODY_30013_Sorted.Y",
  m_UseType = USE_TYPE.UT_ATTACH_NORMAL,
  m_AttachFrameName = "Bip01_Pelvis",
  m_ShopImage = "HQ_Shop_COMMON_Elite_AC_LOWBODY_30013.dds",
  m_DropViewer = "DropItemPouch",
  m_ItemType = ITEM_TYPE.IT_ACCESSORY,
  m_ItemGrade = ITEM_GRADE.IG_ELITE,
  m_bVested = True,
  m_ucMaxSealCount = 5,
  m_Endurance = 0,
  m_Price = 57600,
  m_EqipPosition = EQIP_POSITION.EP_AC_LEG,
  m_Stat = { m_fAtkPhysic = 30, m_fAtkMagic = 30},
  SOCKET_OPTION = {2601}
})
