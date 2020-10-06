#pragma once
#include "Leviathan/Data/Object.h"

#include <functional>
#include <string>

namespace Leviathan::Events {
	enum class EventType {
		None,
		MouseMoveEvent,
		MousePressEvent,
		MouseReleaseEvent,
		MouseWheelEvent,

		KeyPressEvent,
		KeyReleaseEvent,
		KeyRepeatEvent,
		KeyTypeEvent,

		RefreshEvent,
		ResizeEvent,
		MoveEvent,
		CloseEvent,
		FocusEvent,
		LostFocusEvent
	};

	enum class EventCategory {
		None,
		MouseEvent,
		KeyboardEvent,
		WindowEvent
	};

	class  Event : public Object {
	public:
		inline const EventType GetType() { return this->type; }
		inline const EventCategory GetCategory() { return this->category; }

		virtual inline std::string ToString() override { return "Empty event"; }
	protected:
		EventCategory category = EventCategory::None;
		EventType type = EventType::None;
		bool handled = false;
	};

#pragma region Window_Events
	class  RefreshEvent : public Event {
	public:
		RefreshEvent(double frametime);
		~RefreshEvent() = default;
		inline double GetFrametime() { return frametime; }
		std::string ToString() override;
	private:
		double frametime;
	};

	class  ResizeEvent : public Event {
	public:
		ResizeEvent(int size_x, int size_y);
		~ResizeEvent() = default;
		inline void GetSize(int* x, int* y) { *x = size_x; *y = size_y; }
		std::string ToString() override;
	private:
		int size_x, size_y;
	};

	class  MoveEvent : public Event {
	public:
		MoveEvent(int x, int y);
		~MoveEvent() = default;
		inline void GetPos(int* x, int* y) { *x = this->x; *y = this->y; }
		std::string ToString() override;
	private:
		int x, y;
	};

	class  FocusEvent : public Event {
	public:
		FocusEvent(int hasfocus);
		~FocusEvent() = default;
		inline bool hasFocus() { return hasfocus; };
		std::string ToString() override;
	private:
		bool hasfocus;
	};
#pragma endregion

#pragma region Mouse_Events
	class  MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(double x_pos, double y_pos, double x_delta, double y_delta);
		~MouseMoveEvent() = default;
		std::string ToString() override;
		inline void GetPosition(double* x, double* y) { *x = x_pos; *y = y_pos; }
		inline void GetDelta(double* dx, double* dy) { *dx = x_delta; *dy = y_delta; }
	private:
		double x_pos, y_pos;
		double x_delta, y_delta;
	};

	class  MousePressEvent : public Event {
	public:
		MousePressEvent(int button);
		~MousePressEvent() = default;
		std::string ToString() override;
		inline int GetButton() { return button; }
	private:
		int button;
	};

	class  MouseReleaseEvent : public Event {
	public:
		MouseReleaseEvent(int button);
		~MouseReleaseEvent() = default;
		std::string ToString() override;
		inline int GetButton() { return button; }
	private:
		int button;
	};

	class  MouseWheelEvent : public Event {
	public:
		MouseWheelEvent(double x, double y);
		~MouseWheelEvent() = default;
		std::string ToString() override;
		inline void GetScroll(double* x, double* y) { *x = x_scroll; *y = y_scroll; }
	private:
		double x_scroll, y_scroll;
	};
#pragma endregion

#pragma region Keyboard_Event
	class  KeyPressEvent : public Event {
	public:
		KeyPressEvent(int key);
		~KeyPressEvent() = default;
		std::string ToString() override;
		inline int GetKey() { return key; }
	private:
		int key;
	};

	class  KeyReleaseEvent : public Event {
	public:
		KeyReleaseEvent(int key);
		~KeyReleaseEvent() = default;
		std::string ToString() override;
		inline int GetKey() { return key; }
	protected:
		int key;
	};

	class  KeyRepeatEvent : public Event {
	public:
		KeyRepeatEvent(int key);
		~KeyRepeatEvent() = default;
		std::string ToString() override;
		inline int GetKey() { return key; }
	protected:
		int key;
	};

	class  KeyTypeEvent : public Event {
	public:
		KeyTypeEvent(int key);
		~KeyTypeEvent() = default;
		std::string ToString() override;
		inline int GetKey() { return key; }
	protected:
		int key;
	};
#pragma endregion

}


