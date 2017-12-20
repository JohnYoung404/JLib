#pragma once
#include <boost/msm/front/euml/euml.hpp>
#include <boost/msm/front/euml/state_grammar.hpp>
#include <boost/msm/back/state_machine.hpp>
#include "jTestBase.h"

namespace msm = boost::msm;
using namespace boost::msm::front::euml;

namespace jLib {

	BOOST_MSM_EUML_STATE((), Off)

	BOOST_MSM_EUML_STATE((), On)

	BOOST_MSM_EUML_EVENT(press)

	BOOST_MSM_EUML_ACTION(switch_light)
	{
		template <class Event, class Fsm>
		void operator()(const Event &ev, Fsm &fsm,
			BOOST_MSM_EUML_STATE_NAME(Off) &sourceState,
			BOOST_MSM_EUML_STATE_NAME(On) &targetState) const
		{
			std::cout << "Switching on\n";
		}

		template <class Event, class Fsm>
		void operator()(const Event &ev, Fsm &fsm,
			decltype(On) &sourceState,
			decltype(Off) &targetState) const
		{
			std::cout << "Switching off\n";
		}
	};

	BOOST_MSM_EUML_TRANSITION_TABLE((
		Off + press / switch_light == On,
		On + press / switch_light == Off
		), light_transition_table)

	BOOST_MSM_EUML_DECLARE_STATE_MACHINE(
	(light_transition_table, init_ << Off),
		light_state_machine)

	class jMsmTest final : public jITestable {
	public:
		virtual void test() override {
			jITestable::test();

			msm::back::state_machine<light_state_machine> light;
			light.process_event(press);
			light.process_event(press);
		}
	};

}