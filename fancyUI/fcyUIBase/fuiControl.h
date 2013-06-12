////////////////////////////////////////////////////////////////////////////////
/// @file  fuiControl.h
/// @brief fancyUI 控件基类
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fuiProperty.h"
#include "fuiEvent.h"
#include "fuiStyle.h"

#include <string>
#include <unordered_map>

class fuiPage;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancyUI控件基类
////////////////////////////////////////////////////////////////////////////////
class fuiControl :
	public fcyRefObjImpl<fcyRefObj>, 
	public fuiPropertySet, 
	public fuiEventSet
{
	friend class fuiControl;
	friend class fuiPage;
protected:
	/// @brief 根控件
	fuiPage* m_pRootPage;

	/// @brief 控件样式
	fuiStyle* m_pStyle;

	/// @brief 父对象
	fuiControl* m_pParent;
	
	/// @brief 子控件
	/// @note  索引越小越底层
	std::vector<fcyRefPointer<fuiControl> > m_SubControlList;

	// ========== 属性&事件 ==========
protected: // 属性
	// 属性成员
	std::wstring m_Name;    ///< @brief [只读] 控件名
	fcyRect m_Rect;         ///< @brief [读写] 控件位置
	fBool m_bClip;          ///< @brief [读写] 裁剪

	// 访问器
	fuiPropertyAccessor<std::wstring> m_Name_Accessor; ///< @brief 控件名访问器 
	fuiPropertyAccessor<fcyRect> m_Rect_Accessor;      ///< @brief 控件范围访问器
	fuiPropertyAccessor<float> m_Left_Accessor;        ///< @brief 左侧距离访问器 
	fuiPropertyAccessor<float> m_Top_Accessor;         ///< @brief 顶端距离访问器 
	fuiPropertyAccessor<float> m_Width_Accessor;       ///< @brief 宽度访问器 
	fuiPropertyAccessor<float> m_Height_Accessor;      ///< @brief 高度访问器
	fuiPropertyAccessor<bool> m_Clip_Accessor;         ///< @brief 裁剪访问器

	// 注册所有默认属性
	void registerAllProperty();
public: // 事件
	/// @brief     执行控件事件
	/// @param[in] Str   事件名称
	/// @param[in] pArgs 事件参数
	void ExecEvent(const std::wstring& Str, fuiEventArgs* pArgs = &fuiDelegate::EmptyEventArgs)
	{
		fuiEventSet::ExecEvent(Str, this, pArgs);
	}
protected:
	// 注册所有默认事件
	void registerAllEvent();
	
	// ========== 控件基础属性操作 ==========
protected: // for fuiControl
	/// @brief  增加一个子控件
	/// @return 返回父控件指针
	virtual fuiControl* attachSubControl(fuiControl* pControl);
	/// @brief  移除一个子控件
	virtual void removeSubControl(fuiControl* pControl);
	/// @brief 查询子控件的层次
	virtual fuInt getSubControlLayer(const fuiControl* pControl);
	/// @brief 设置子控件的层次
	virtual void setSubControlLayer(fuiControl* pControl, fInt Index);
public:
	// === 未注册属性 ===
	/// @brief 获得根控件
	fuiPage* GetRoot()const { return m_pRootPage; }
	/// @brief 获得父对象
	fuiControl* GetParent()const { return m_pParent; }
	/// @brief 设置父对象
	void SetParent(fuiControl* pParent);
	/// @brief 查询在父对象的绝对层次
	fuInt GetLayer()const;
	/// @brief     设置在父对象的层次
	/// @param[in] Layer 相对层次，-1表示顶层，0表示底层
	void SetLayer(fInt Layer);
	/// @brief 返回子控件数目
	virtual fuInt GetSubControlCount()const;
	/// @brief     返回子控件
	/// @note      弱引用
	/// @param[in] Layer 相对层次
	virtual fuiControl* GetSubControl(fInt Layer);
	/// @brief 查询控件样式
	virtual fuiStyle* GetControlStyle()const;
	/// @brief 设置控件样式
	virtual void SetControlStyle(fuiStyle* pStyle);

	// === 快速访问属性 ===
	/// @brief 获得控件唯一名称
	const std::wstring& GetName()const { return m_Name; }
	/// @brief 获得控件矩形位置
	const fcyRect& GetRect()const { return m_Rect; }
	/// @brief 设置控件矩形位置
	void SetRect(const fcyRect& Rect);
	/// @brief 获得控件左边位置
	fFloat GetLeft()const { return m_Rect.a.x; }
	/// @brief 设置控件左边位置
	void SetLeft(fFloat Value);
	/// @brief 获得控件顶边位置
	fFloat GetTop()const { return m_Rect.a.y; }
	/// @brief 设置控件顶边位置
	void SetTop(fFloat Value);
	/// @brief 返回控件宽度
	fFloat GetWidth()const { return m_Rect.GetWidth(); }
	/// @brief 设置控件宽度
	void SetWidth(fFloat Value);
	/// @brief 返回控件高度
	fFloat GetHeight()const { return m_Rect.GetHeight(); }
	/// @brief 设置控件高度
	void SetHeight(fFloat Value);
	/// @brief 返回是否裁剪
	fBool GetClip()const { return m_bClip; }
	/// @brief 设置是否裁剪
	void SetClip(fBool Value) { m_bClip = Value; }
public:  // 覆写操作
	/// @brief 更新控件状态
	virtual void Update(fDouble ElapsedTime) {}
	/// @brief 渲染控件
	virtual void Render(fuiGraphics* pGraph) {}
	/// @brief     Hit测试
	/// @param[in] Pos 相对控件左上角的位置
	virtual fBool HitTest(const fcyVec2& Pos) { return true; }
private:   // 禁止拷贝
	fuiControl(const fuiControl& Org);
	fuiControl& operator=(const fuiControl& Right);
protected: // 禁止创建
	fuiControl(fuiPage* pRootControl, const std::wstring& Name);
protected: // 禁止栈对象
	virtual ~fuiControl();
};
