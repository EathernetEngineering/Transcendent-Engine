#pragma once

namespace TE {
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define TE_KEY_SPACE           ::TE::Key::Space
#define TE_KEY_APOSTROPHE      ::TE::Key::Apostrophe    /* ' */
#define TE_KEY_COMMA           ::TE::Key::Comma         /* , */
#define TE_KEY_MINUS           ::TE::Key::Minus         /* - */
#define TE_KEY_PERIOD          ::TE::Key::Period        /* . */
#define TE_KEY_SLASH           ::TE::Key::Slash         /* / */
#define TE_KEY_0               ::TE::Key::D0
#define TE_KEY_1               ::TE::Key::D1
#define TE_KEY_2               ::TE::Key::D2
#define TE_KEY_3               ::TE::Key::D3
#define TE_KEY_4               ::TE::Key::D4
#define TE_KEY_5               ::TE::Key::D5
#define TE_KEY_6               ::TE::Key::D6
#define TE_KEY_7               ::TE::Key::D7
#define TE_KEY_8               ::TE::Key::D8
#define TE_KEY_9               ::TE::Key::D9
#define TE_KEY_SEMICOLON       ::TE::Key::Semicolon     /* ; */
#define TE_KEY_EQUAL           ::TE::Key::Equal         /* = */
#define TE_KEY_A               ::TE::Key::A
#define TE_KEY_B               ::TE::Key::B
#define TE_KEY_C               ::TE::Key::C
#define TE_KEY_D               ::TE::Key::D
#define TE_KEY_E               ::TE::Key::E
#define TE_KEY_F               ::TE::Key::F
#define TE_KEY_G               ::TE::Key::G
#define TE_KEY_H               ::TE::Key::H
#define TE_KEY_I               ::TE::Key::I
#define TE_KEY_J               ::TE::Key::J
#define TE_KEY_K               ::TE::Key::K
#define TE_KEY_L               ::TE::Key::L
#define TE_KEY_M               ::TE::Key::M
#define TE_KEY_N               ::TE::Key::N
#define TE_KEY_O               ::TE::Key::O
#define TE_KEY_P               ::TE::Key::P
#define TE_KEY_Q               ::TE::Key::Q
#define TE_KEY_R               ::TE::Key::R
#define TE_KEY_S               ::TE::Key::S
#define TE_KEY_T               ::TE::Key::T
#define TE_KEY_U               ::TE::Key::U
#define TE_KEY_V               ::TE::Key::V
#define TE_KEY_W               ::TE::Key::W
#define TE_KEY_X               ::TE::Key::X
#define TE_KEY_Y               ::TE::Key::Y
#define TE_KEY_Z               ::TE::Key::Z
#define TE_KEY_LEFT_BRACKET    ::TE::Key::LeftBracket   /* [ */
#define TE_KEY_BACKSLASH       ::TE::Key::Backslash     /* \ */
#define TE_KEY_RIGHT_BRACKET   ::TE::Key::RightBracket  /* ] */
#define TE_KEY_GRAVE_ACCENT    ::TE::Key::GraveAccent   /* ` */
#define TE_KEY_WORLD_1         ::TE::Key::World1        /* non-US #1 */
#define TE_KEY_WORLD_2         ::TE::Key::World2        /* non-US #2 */

/* Function keys */
#define TE_KEY_ESCAPE          ::TE:Key::Escape
#define TE_KEY_ENTER           ::TE:Key::Enter
#define TE_KEY_TAB             ::TE:Key::Tab
#define TE_KEY_BACKSPACE       ::TE:Key::Backspace
#define TE_KEY_INSERT          ::TE:Key::Insert
#define TE_KEY_DELETE          ::TE:Key::Delete
#define TE_KEY_RIGHT           ::TE:Key::Right
#define TE_KEY_LEFT            ::TE:Key::Left
#define TE_KEY_DOWN            ::TE:Key::Down
#define TE_KEY_UP              ::TE:Key::Up
#define TE_KEY_PAGE_UP         ::TE:Key::PageUp
#define TE_KEY_PAGE_DOWN       ::TE:Key::PageDown
#define TE_KEY_HOME            ::TE:Key::Home
#define TE_KEY_END             ::TE:Key::End
#define TE_KEY_CAPS_LOCK       ::TE:Key::CapsLock
#define TE_KEY_SCROLL_LOCK     ::TE:Key::ScrollLock
#define TE_KEY_NUM_LOCK        ::TE:Key::NumLock
#define TE_KEY_PRINT_SCREEN    ::TE:Key::PrintScreen
#define TE_KEY_PAUSE           ::TE:Key::Pause
#define TE_KEY_F1              ::TE:Key::F1
#define TE_KEY_F2              ::TE:Key::F2
#define TE_KEY_F3              ::TE:Key::F3
#define TE_KEY_F4              ::TE:Key::F4
#define TE_KEY_F5              ::TE:Key::F5
#define TE_KEY_F6              ::TE:Key::F6
#define TE_KEY_F7              ::TE:Key::F7
#define TE_KEY_F8              ::TE:Key::F8
#define TE_KEY_F9              ::TE:Key::F9
#define TE_KEY_F10             ::TE:Key::F10
#define TE_KEY_F11             ::TE:Key::F11
#define TE_KEY_F12             ::TE:Key::F12
#define TE_KEY_F13             ::TE:Key::F13
#define TE_KEY_F14             ::TE:Key::F14
#define TE_KEY_F15             ::TE:Key::F15
#define TE_KEY_F16             ::TE:Key::F16
#define TE_KEY_F17             ::TE:Key::F17
#define TE_KEY_F18             ::TE:Key::F18
#define TE_KEY_F19             ::TE:Key::F19
#define TE_KEY_F20             ::TE:Key::F20
#define TE_KEY_F21             ::TE:Key::F21
#define TE_KEY_F22             ::TE:Key::F22
#define TE_KEY_F23             ::TE:Key::F23
#define TE_KEY_F24             ::TE:Key::F24
#define TE_KEY_F25             ::TE:Key::F25

/* Keypad */
#define TE_KEY_KP_0            ::TE::Key::KP0
#define TE_KEY_KP_1            ::TE::Key::KP1
#define TE_KEY_KP_2            ::TE::Key::KP2
#define TE_KEY_KP_3            ::TE::Key::KP3
#define TE_KEY_KP_4            ::TE::Key::KP4
#define TE_KEY_KP_5            ::TE::Key::KP5
#define TE_KEY_KP_6            ::TE::Key::KP6
#define TE_KEY_KP_7            ::TE::Key::KP7
#define TE_KEY_KP_8            ::TE::Key::KP8
#define TE_KEY_KP_9            ::TE::Key::KP9
#define TE_KEY_KP_DECIMAL      ::TE::Key::KPDecimal
#define TE_KEY_KP_DIVIDE       ::TE::Key::KPDivide
#define TE_KEY_KP_MULTIPLY     ::TE::Key::KPMultiply
#define TE_KEY_KP_SUBTRACT     ::TE::Key::KPSubtract
#define TE_KEY_KP_ADD          ::TE::Key::KPAdd
#define TE_KEY_KP_ENTER        ::TE::Key::KPEnter
#define TE_KEY_KP_EQUAL        ::TE::Key::KPEqual

#define TE_KEY_LEFT_SHIFT      ::TE::Key::LeftShift
#define TE_KEY_LEFT_CONTROL    ::TE::Key::LeftControl
#define TE_KEY_LEFT_ALT        ::TE::Key::LeftAlt
#define TE_KEY_LEFT_SUPER      ::TE::Key::LeftSuper
#define TE_KEY_RIGHT_SHIFT     ::TE::Key::RightShift
#define TE_KEY_RIGHT_CONTROL   ::TE::Key::RightControl
#define TE_KEY_RIGHT_ALT       ::TE::Key::RightAlt
#define TE_KEY_RIGHT_SUPER     ::TE::Key::RightSuper
#define TE_KEY_MENU            ::TE::Key::Menu
