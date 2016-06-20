#include "skillSet.h"
#include <ssl_common/grSimComm.h>
#include <ssl_common/geometry.hpp>
#include <ssl_common/config.h>
#include <fstream>

#define FRICTION_COEFF (0.05)
#define ACCN_GRAVITY (9.80665)

namespace Strategy{
	gr_Robot_Command SkillSet::dribbleTurn(const SParam &param, const BeliefState &state, int botID)
	{
		Vector2D<int> point(param.DribbleTurnP.x, param.DribbleTurnP.y);
		Vector2D<int> botPos(state.homePos[botID].x, state.homePos[botID].y);
    	Vector2D<int> ballPos(state.ballPos.x, state.ballPos.y);
    	float radius = param.DribbleTurnP.turn_radius;
    	float finalSlope = Vector2D<int>::angle(point, ballPos);
    	float turnAngleLeft = normalizeAngle(finalSlope - state.homePos[botID].theta)+10*PI/180; // Angle left to turn
    //	float omega = turnAngleLeft * param.DribbleTurnP.max_omega / (2 * PI);
       float omega=param.DribbleTurnP.max_omega*(turnAngleLeft<0?-1:1);
    	float phi = atan2(FRICTION_COEFF*ACCN_GRAVITY,omega*omega*radius) + 20.0*PI/180;//*(omega<0?(-1):1);
     //   std::fstream f;
     //   f.open("/home/animesh/Documents/robocup/a.txt",std::ios::out|std::ios::app);
     //   f<<"Phi: "<<phi*180/(PI)<<" Angle left: "<<turnAngleLeft*180/(PI)<<"\n";
     //   f.close();
    	float sphi=sin(phi),cphi=cos(phi);
    	float v_x=omega*radius*sphi,v_y=omega*radius*cphi;
    	return getRobotCommandMessage(botID, v_x, v_y, omega, 0, true);
	}
}