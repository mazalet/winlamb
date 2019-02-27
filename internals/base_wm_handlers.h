/**
 * Part of WinLamb - Win32 API Lambda Library
 * https://github.com/rodrigocfd/winlamb
 * Copyright 2017-present Rodrigo Cesar de Freitas Dias
 * This library is released under the MIT License
 */

#pragma once
#include "base_msg.h"
#include "params_wm.h"

namespace wl {
namespace wli {

// Exposes functions to add lambda handlers to all documented Windows messages.
template<typename retT>
class base_wm_handlers final {
private:
	base_msg<retT>& _baseMsg;

public:
	base_wm_handlers(base_msg<retT>& baseMsg) noexcept :
		_baseMsg(baseMsg) { }

	void operator()(UINT msg, std::function<retT(params)>&& func) {
		this->_msg(msg, std::move(func));
	}
	void operator()(std::initializer_list<UINT> msgs,
		std::function<retT(params)>&& func)
	{
		this->_baseMsg.throw_if_cant_add();
		this->_baseMsg.msgs.add(msgs, std::move(func));
	}

	void command(WORD cmd, std::function<retT(wm::command)>&& func) {
		this->_baseMsg.throw_if_cant_add();
		this->_baseMsg.cmds.add(cmd, std::move(func));
	}
	void command(std::initializer_list<WORD> cmds,
		std::function<retT(wm::command)>&& func)
	{
		this->_baseMsg.throw_if_cant_add();
		this->_baseMsg.cmds.add(cmds, std::move(func));
	}

#define WINLAMB_HANDLERWM(mname, umsg) \
	void mname(std::function<retT(wm::mname)>&& func) { \
		this->_msg(umsg, std::move(func)); \
	}

	WINLAMB_HANDLERWM(activate)
	WINLAMB_HANDLERWM(activate_app)
	WINLAMB_HANDLERWM(ask_cb_format_name)
	WINLAMB_HANDLERWM(cancel_mode)
	WINLAMB_HANDLERWM(capture_changed)
	WINLAMB_HANDLERWM(change_cb_chain)
	WINLAMB_HANDLERWM(char_)
	WINLAMB_HANDLERWM(char_to_item)
	WINLAMB_HANDLERWM(child_activate)
	WINLAMB_HANDLERWM(close)
	WINLAMB_HANDLERWM(compacting)
	WINLAMB_HANDLERWM(compare_item)
	WINLAMB_HANDLERWM(context_menu)
	WINLAMB_HANDLERWM(copy_data)
	WINLAMB_HANDLERWM(create)
	WINLAMB_HANDLERWM(ctl_color_btn)
	WINLAMB_HANDLERWM(ctl_color_dlg)
	WINLAMB_HANDLERWM(ctl_color_edit)
	WINLAMB_HANDLERWM(ctl_color_listbox)
	WINLAMB_HANDLERWM(ctl_color_scrollbar)
	WINLAMB_HANDLERWM(ctl_color_static)
	WINLAMB_HANDLERWM(dead_char)
	WINLAMB_HANDLERWM(delete_item)
	WINLAMB_HANDLERWM(destroy)
	WINLAMB_HANDLERWM(destroy_clipboard)
	WINLAMB_HANDLERWM(dev_mode_change)

#ifdef _DBT_H // Ras.h
	WINLAMB_HANDLERWM(device_change)
#endif

	WINLAMB_HANDLERWM(display_change)
	WINLAMB_HANDLERWM(draw_clipboard)
	WINLAMB_HANDLERWM(draw_item)
	WINLAMB_HANDLERWM(drop_files)
	WINLAMB_HANDLERWM(enable)
	WINLAMB_HANDLERWM(end_session)
	WINLAMB_HANDLERWM(enter_idle)
	WINLAMB_HANDLERWM(enter_menu_loop)
	WINLAMB_HANDLERWM(enter_size_move)
	WINLAMB_HANDLERWM(erase_bkgnd)

	WINLAMB_HANDLERWM(init_dialog)

private:
	template<typename funcT>
	void _msg(UINT msg, funcT&& func) {
		this->_baseMsg.throw_if_cant_add();
		this->_baseMsg.msgs.add(msg, std::move(func));
	}
};

}//namespace wli
}//namespace wl
