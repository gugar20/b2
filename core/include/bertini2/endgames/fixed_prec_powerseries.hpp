//This file is part of Bertini 2.
//
//fixed_prec_powerseries_endgame.hpp is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//fixed_prec_powerseries_endgame.hpp is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with fixed_prec_powerseries_endgame.hpp.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright(C) 2015, 2016 by Bertini2 Development Team
//
// See <http://www.gnu.org/licenses/> for a copy of the license, 
// as well as COPYING.  Bertini2 is provided with permitted 
// additional terms in the b2/licenses/ directory.

// individual authors of this file include:
// daniel brake, university of notre dame
// Tim Hodges, Colorado State University




#pragma once

/**
\file fixed_prec_powerseries_endgame.hpp

\brief Contains the fixed precision power series endgame type.
*/

#include "bertini2/endgames/powerseries.hpp"
#include "bertini2/endgames/fixed_prec_endgame.hpp"


namespace bertini{ namespace tracking { namespace endgame {

template<typename TrackerT, typename Enable>
class FixedPrecPowerSeriesEndgame : 
		public PowerSeriesEndgame<TrackerT,
								  FixedPrecPowerSeriesEndgame<TrackerT, typename std::enable_if<TrackerTraits<TrackerT>::IsFixedPrec>::type>>, 
		public FixedPrecEndgamePolicyBase<TrackerT>
{
public:
	using TrackerType = TrackerT;
	using EGType = PowerSeriesEndgame<TrackerType, FixedPrecPowerSeriesEndgame>;
	using BRT = typename TrackerTraits<TrackerType>::BaseRealType;

	using Configs = typename AlgoTraits<EGType>::NeededConfigs;


	template<typename CT>
	SuccessCode RefineSample(Vec<CT> & result, Vec<CT> const& current_sample, CT const& current_time) const
	{
		using RT = mpfr_float;
		using std::max;
		auto& TR = this->GetTracker();

		auto refinement_success = this->GetTracker().Refine(result,current_sample,current_time,
		                          	this->FinalTolerance()/100,
		                          	this->EndgameSettings().max_num_newton_iterations);

		return SuccessCode::Success;
	}

public:
	explicit FixedPrecPowerSeriesEndgame(TrackerType const& tr, 
	                                	typename Configs::ToTuple const& settings )
      : EGType(tr, settings)
   	{}

    template< typename... Ts >
		FixedPrecPowerSeriesEndgame(TrackerType const& tr, const Ts&... ts ) : 
			FixedPrecPowerSeriesEndgame(tr, Configs::Unpermute( ts... ) ) 
		{}

};




}}} // re: namespaces
