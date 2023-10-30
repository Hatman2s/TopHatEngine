#pragma once

namespace TopHat
{
	class Time
	{
	public:
		static float GetTime();
	};

	class DeltaTime
	{
	public:

		DeltaTime():m_DeltaT(0) {};
		operator float() { return m_DeltaT ; }

		void CalculateDeltaTime()
		{
			m_New = Time::GetTime();
			m_DeltaT = m_New - m_Prev;
			m_Prev = m_New;
		}
		 
	private:
		float m_DeltaT, m_Prev, m_New;

		
	};
}
