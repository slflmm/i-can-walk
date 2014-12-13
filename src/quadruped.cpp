#include <iostream>

#include "Quadruped.h"

const double pi = 3.1415926535897;
#define DEG_TO_RAD pi/360.0

/**
constants that define the HexaL3J (quadruped robot) described in Heinen 2006.
**/
static const double PAW_X = 0.08;
static const double PAW_Y = 0.09;
static const double PAW_Z = 0.05;

static const double SHIN_X = 0.05;
static const double SHIN_Y = 0.05;
static const double SHIN_Z = 0.15;

static const double THIGH_X = 0.05;
static const double THIGH_Y = 0.05;
static const double THIGH_Z = 0.15;

static const double CHEST_X = 0.45;
static const double CHEST_Y = 0.25;
static const double CHEST_Z = 0.15;

static const double CHEST_HEIGHT = PAW_Z + SHIN_Z + THIGH_Z + CHEST_Z/2.0;
static const double THIGH_HEIGHT = PAW_Z + SHIN_Z + THIGH_Z/2.0;
static const double SHIN_HEIGHT = PAW_Z + SHIN_Z/2.0;
static const double PAW_HEIGHT = PAW_Z/2.0;

static const double CHEST_POS[3] = {0.0, 0.0, CHEST_HEIGHT};

static const double FRONT_RIGHT_THIGH_POS[3] = {CHEST_X/2.0-THIGH_X/2.0, CHEST_Y/2.0-THIGH_Y/2.0, THIGH_HEIGHT};
static const double FRONT_LEFT_THIGH_POS[3] = {CHEST_X/2.0-THIGH_X/2.0, THIGH_Y/2.0-CHEST_Y/2.0, THIGH_HEIGHT};
static const double BACK_RIGHT_THIGH_POS[3] = {THIGH_X/2.0-CHEST_X/2.0, THIGH_Y/2.0-CHEST_Y/2.0, THIGH_HEIGHT};
static const double BACK_LEFT_THIGH_POS[3] = {THIGH_X/2.0-CHEST_X/2.0, CHEST_Y/2.0-THIGH_Y/2.0, THIGH_HEIGHT};

static const double FRONT_RIGHT_SHIN_POS[3] = {CHEST_X/2.0-SHIN_X/2.0, CHEST_Y/2.0-SHIN_Y/2.0, SHIN_HEIGHT};
static const double FRONT_LEFT_SHIN_POS[3] = {CHEST_X/2.0-SHIN_X/2.0, SHIN_Y/2.0-CHEST_Y/2.0, SHIN_HEIGHT};
static const double BACK_RIGHT_SHIN_POS[3] = {SHIN_X/2.0-CHEST_X/2.0, SHIN_Y/2.0-CHEST_Y/2.0, SHIN_HEIGHT};
static const double BACK_LEFT_SHIN_POS[3] = {SHIN_X/2.0-CHEST_X/2.0, CHEST_Y/2.0-SHIN_Y/2.0, SHIN_HEIGHT};

static const double FRONT_RIGHT_PAW_POS[3] = {CHEST_X/2.0-SHIN_X/2.0, CHEST_Y/2.0-SHIN_Y/2.0, PAW_HEIGHT};
static const double FRONT_LEFT_PAW_POS[3] = {CHEST_X/2.0-SHIN_X/2.0, SHIN_Y/2.0-CHEST_Y/2.0, PAW_HEIGHT};
static const double BACK_RIGHT_PAW_POS[3] = {SHIN_X/2.0-CHEST_X/2.0, SHIN_Y/2.0-CHEST_Y/2.0, PAW_HEIGHT};
static const double BACK_LEFT_PAW_POS[3] = {SHIN_X/2.0-CHEST_X/2.0, CHEST_Y/2.0-SHIN_Y/2.0, PAW_HEIGHT};

static const double FRONT_RIGHT_HIP_POS[3] = {CHEST_X/2.0-THIGH_X/2.0, CHEST_Y/2.0-THIGH_Y/2.0, THIGH_HEIGHT + THIGH_Z/2.0};
static const double FRONT_LEFT_HIP_POS[3] = {CHEST_X/2.0-THIGH_X/2.0, THIGH_Y/2.0-CHEST_Y/2.0, THIGH_HEIGHT + THIGH_Z/2.0};
static const double BACK_RIGHT_HIP_POS[3] = {THIGH_X/2.0-CHEST_X/2.0, THIGH_Y/2.0-CHEST_Y/2.0, THIGH_HEIGHT + THIGH_Z/2.0};
static const double BACK_LEFT_HIP_POS[3] = {THIGH_X/2.0-CHEST_X/2.0, CHEST_Y/2.0-THIGH_Y/2.0, THIGH_HEIGHT + THIGH_Z/2.0};

static const double FRONT_RIGHT_KNEE_POS[3] = {CHEST_X/2.0-SHIN_X/2.0, CHEST_Y/2.0-SHIN_Y/2.0, SHIN_HEIGHT + SHIN_Z/2.0};
static const double FRONT_LEFT_KNEE_POS[3] = {CHEST_X/2.0-SHIN_X/2.0, SHIN_Y/2.0-CHEST_Y/2.0, SHIN_HEIGHT + SHIN_Z/2.0};
static const double BACK_RIGHT_KNEE_POS[3] = {SHIN_X/2.0-CHEST_X/2.0, SHIN_Y/2.0-CHEST_Y/2.0, SHIN_HEIGHT + SHIN_Z/2.0};
static const double BACK_LEFT_KNEE_POS[3] = {SHIN_X/2.0-CHEST_X/2.0, CHEST_Y/2.0-SHIN_Y/2.0, SHIN_HEIGHT + SHIN_Z/2.0};

static const double FRONT_RIGHT_ANKLE_POS[3] = {CHEST_X/2.0-SHIN_X/2.0, CHEST_Y/2.0-SHIN_Y/2.0, PAW_HEIGHT + PAW_Z/2.0};
static const double FRONT_LEFT_ANKLE_POS[3] = {CHEST_X/2.0-SHIN_X/2.0, SHIN_Y/2.0-CHEST_Y/2.0, PAW_HEIGHT + PAW_Z/2.0};
static const double BACK_RIGHT_ANKLE_POS[3] = {SHIN_X/2.0-CHEST_X/2.0, SHIN_Y/2.0-CHEST_Y/2.0, PAW_HEIGHT + PAW_Z/2.0};
static const double BACK_LEFT_ANKLE_POS[3] = {SHIN_X/2.0-CHEST_X/2.0, CHEST_Y/2.0-SHIN_Y/2.0, PAW_HEIGHT + PAW_Z/2.0};

static const double HIP_JOINT_RESTRICTIONS[2] = {-60*DEG_TO_RAD, 15*DEG_TO_RAD};
static const double KNEE_JOINT_RESTRICTIONS[2] = {-1*DEG_TO_RAD, 120*DEG_TO_RAD};
static const double ANKLE_JOINT_RESTRICTIONS[2] = {-90*DEG_TO_RAD, 30*DEG_TO_RAD};


vector<double> extendGenome(vector<double> g)
{
  vector<double> extended;
  for (int i = 0; i < 4; i++)
  {
    extended.push_back(g[i]);
  }

  for (int i = 4; i < g.size(); i+=4)
  {
    // right limb
    extended.push_back(g[i]);
    extended.push_back(g[i+1]);
    extended.push_back(g[i+2]);
    extended.push_back(g[i+3]);

    // left limb
    extended.push_back(g[i+2]);
    extended.push_back(g[i+3]);
    extended.push_back(g[i]);
    extended.push_back(g[i+1]);
  }
  return extended;
}

Quadruped::Quadruped()
{

}

Quadruped::Quadruped(dWorldID pWorld, dSpaceID pSpace, int pDensity, double* pOffset, vector<double> pGenome)
{


  world = pWorld;
  space = pSpace;
  density = pDensity;

  offset = pOffset;
  state = 0;

  genome = extendGenome(pGenome);


  // make the chest
  MyBody chest = addBody(CHEST_X, CHEST_Y, CHEST_Z, CHEST_POS);

  // make the thighs
  MyBody front_right_thigh = addBody(THIGH_X, THIGH_Y, THIGH_Z, FRONT_RIGHT_THIGH_POS);
  MyBody front_left_thigh = addBody(THIGH_X, THIGH_Y, THIGH_Z, FRONT_LEFT_THIGH_POS);
  MyBody back_right_thigh = addBody(THIGH_X, THIGH_Y, THIGH_Z, BACK_RIGHT_THIGH_POS);
  MyBody back_left_thigh = addBody(THIGH_X, THIGH_Y, THIGH_Z, BACK_LEFT_THIGH_POS);

  // make the shins
  MyBody front_right_shin = addBody(SHIN_X, SHIN_Y, SHIN_Z, FRONT_RIGHT_SHIN_POS);
  MyBody front_left_shin = addBody(SHIN_X, SHIN_Y, SHIN_Z, FRONT_LEFT_SHIN_POS);
  MyBody back_right_shin = addBody(SHIN_X, SHIN_Y, SHIN_Z, BACK_RIGHT_SHIN_POS);
  MyBody back_left_shin = addBody(SHIN_X, SHIN_Y, SHIN_Z, BACK_LEFT_SHIN_POS);

  // make the paws
  MyBody front_right_paw = addBody(PAW_X, PAW_Y, PAW_Z, FRONT_RIGHT_PAW_POS);
  MyBody front_left_paw = addBody(PAW_X, PAW_Y, PAW_Z, FRONT_LEFT_PAW_POS);
  MyBody back_right_paw = addBody(PAW_X, PAW_Y, PAW_Z, BACK_RIGHT_PAW_POS);
  MyBody back_left_paw = addBody(PAW_X, PAW_Y, PAW_Z, BACK_LEFT_PAW_POS);

  // add hip joints
  addHingeJoint(chest.body, front_right_thigh.body, FRONT_RIGHT_HIP_POS, HIP_JOINT_RESTRICTIONS);
  addHingeJoint(chest.body, front_left_thigh.body, FRONT_LEFT_HIP_POS,  HIP_JOINT_RESTRICTIONS);
  addHingeJoint(chest.body, back_right_thigh.body, BACK_RIGHT_HIP_POS, HIP_JOINT_RESTRICTIONS);
  addHingeJoint(chest.body, back_left_thigh.body, BACK_LEFT_HIP_POS, HIP_JOINT_RESTRICTIONS);

  // add knee joints
  addHingeJoint(front_right_thigh.body, front_right_shin.body, FRONT_RIGHT_KNEE_POS, KNEE_JOINT_RESTRICTIONS);
  addHingeJoint(front_left_thigh.body, front_left_shin.body, FRONT_LEFT_KNEE_POS, KNEE_JOINT_RESTRICTIONS);
  addHingeJoint(back_right_thigh.body, back_right_shin.body, BACK_RIGHT_KNEE_POS, KNEE_JOINT_RESTRICTIONS);
  addHingeJoint(back_left_thigh.body, back_left_shin.body, BACK_LEFT_KNEE_POS, KNEE_JOINT_RESTRICTIONS);

  // add ankle joints
  addHingeJoint(front_right_shin.body, front_right_paw.body, FRONT_RIGHT_ANKLE_POS, ANKLE_JOINT_RESTRICTIONS);
  addHingeJoint(front_left_shin.body, front_left_paw.body, FRONT_LEFT_ANKLE_POS, ANKLE_JOINT_RESTRICTIONS);
  addHingeJoint(back_right_shin.body, back_right_paw.body, BACK_RIGHT_ANKLE_POS, ANKLE_JOINT_RESTRICTIONS);
  addHingeJoint(back_left_shin.body, back_left_paw.body, BACK_LEFT_ANKLE_POS, ANKLE_JOINT_RESTRICTIONS);
}

void Quadruped::update()
{
  
  int stable = 0;

  // cout << "In state " << state << endl;
  for (int i = 0; i < joints.size(); ++i)
  {
    MyJoint myJoint = joints[i];
    double error = (genome[state + 4*(i+1)]-dJointGetHingeAngle(myJoint.joint));
    double v = genome[state]*error; // calculate new velocity
    dJointSetHingeParam(myJoint.joint, dParamVel, v); // and apply velocity

    // if close enough to goal...
    if (fabs(error) < DEG_TO_RAD*5) stable++;

    // cout << i << " currently at : " << dJointGetHingeAngle(myJoint.joint) << endl;
    // cout << " wanting to get to: " << genome[state + 4*(i+1)] << endl;
    // cout << "With error " << error << " which is " << (fabs(error) < DEG_TO_RAD*5) << endl;
  }

  // cout << "Stable is at: " << stable << endl;

  if (stable == 12) {
    state = (state+1)%4;
    // cout << "Incremented state" << endl;
  }

    // cout << "New state is " << state << endl;
}

int Quadruped::getState()
{
  return state;
}

void Quadruped::draw()
{
  dsSetColor(1.0, 1.0, 1.0); // white robot
  for (MyBody body : bodies)
  {
    const dReal* pos = dBodyGetPosition(body.body);
    const dReal* rot = dBodyGetRotation(body.body);
    dReal dimensions[3] = {body.lx, body.ly, body.lz};
    dsDrawBoxD(pos, rot, dimensions);
  }
}

const double Quadruped::getX()
{
  return dBodyGetPosition(bodies[0].body)[0];
}

const double Quadruped::getY()
{
  return dBodyGetPosition(bodies[0].body)[1];
}

const double Quadruped::getZ()
{
  return dBodyGetPosition(bodies[0].body)[2];
}


MyBody Quadruped::addBody(double lx, double ly, double lz, const double pos[3])
{
  MyBody myBody;
  myBody.body = dBodyCreate(world);
  myBody.lx = lx;
  myBody.ly = ly;
  myBody.lz = lz;

  dBodySetPosition(myBody.body, pos[0] + offset[0], pos[1] + offset[1], pos[2] + offset[2]);

  dMass m;
  dMassSetZero(&m);
  dMassSetBoxTotal(&m, density, lx, ly, lz);
  dBodySetMass(myBody.body, &m);

  myBody.geom = dCreateBox(space, lx, ly, lz);
  dGeomSetBody(myBody.geom, myBody.body);

  bodies.push_back(myBody);

  return myBody;
}

void Quadruped::addHingeJoint(dBodyID body1, dBodyID body2, const double anchor[3], const double restrictions[2]) // double targets[4]
{
  MyJoint myJoint;
  myJoint.joint = dJointCreateHinge(world, 0);
  // myJoint.targets = {restrictions[0],restrictions[1]};

  dJointAttach(myJoint.joint, body1, body2);
  dJointSetHingeAnchor(myJoint.joint, anchor[0], anchor[1], anchor[2]);
  dJointSetHingeAxis(myJoint.joint, 0.0, -1.0, 0.0);
  dJointSetHingeParam(myJoint.joint, dParamLoStop, restrictions[0]);
  dJointSetHingeParam(myJoint.joint, dParamHiStop, restrictions[1]);
  dJointSetHingeParam(myJoint.joint, dParamFMax, 2000.0);

  joints.push_back(myJoint);
}

