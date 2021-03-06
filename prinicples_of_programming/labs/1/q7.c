/*
 * Author: Amartya Vadlamani
 * Notes: Ok, this one was fun, I took a .jpg of mallet place, manually traced
 *        it into an svg and then extracted all of the coordinates out of that svg
 *        using vim and sed, and then I converted that data into a C program
 */
#include "graphics.h"

void myDrawLine(float x1, float y1, float x2, float y2){
    float scale = 1.6; // a global scale to bring the svg coords into normal values
    int trans_x = -280;
    int trans_y = -450;
    drawLine((int)(x1*scale) + trans_x,
             (int)(y1*scale) + trans_y,
             (int)(x2*scale) + trans_x,
             (int)(y2*scale) + trans_y);
}

int main(){
    myDrawLine(221.5,297.5,178.5,334);
    myDrawLine(242,297.5,178.5,361.5);
    myDrawLine(270.5,297.5,178.5,457.5);
    myDrawLine(288,297.5,215.5,511);
    myDrawLine(221.5,297.5,288,297.5);
    myDrawLine(212.859,304.834,285.05,306.187);
    myDrawLine(201.532,314.449,281.803,315.75);
    myDrawLine(188.259,325.716,278.186,326.402);
    myDrawLine(178.5,341.5,270.5,343);
    myDrawLine(178.5,361.5,266.267,361.5);
    myDrawLine(178.5,390.5,254.75,391);
    myDrawLine(178.5,432.5,241.667,433.941);
    myDrawLine(288,297.5,290.5,301.5);
    myDrawLine(290.5,301.5,224.5,511);
    myDrawLine(339,297.5,336,301.5);
    myDrawLine(339,297.5,405,299.5);
    myDrawLine(405,299.5,441.5,334);
    myDrawLine(339,297.5,400.5,511);
    myDrawLine(336,301.5,389.5,511);
    myDrawLine(378.303,433.941,441.5,433.941);
    myDrawLine(390.273,475.497,441.5,475.5);
    myDrawLine(396.318,496.484,441.5,496);
    myDrawLine(383.791,452.992,441.5,452.5);
    myDrawLine(369.75,404.25,441.5,404.25);
    myDrawLine(373.677,417.881,441.5,417.5);
    myDrawLine(365.934,391,441.5,390.5);
    myDrawLine(362.75,379.949,441.5,380);
    myDrawLine(360.064,370.625,441.5,371.5);
    myDrawLine(357.436,361.5,441.5,361.5);
    myDrawLine(355.729,355.578,441.5,356);
    myDrawLine(353.676,348.449,441.5,350.5);
    myDrawLine(351.891,342.25,441.5,342.25);
    myDrawLine(350.216,336.438,441.5,337.5);
    myDrawLine(348.848,331.688,441.5,334);
    myDrawLine(346.186,322.446,431.241,324.303);
    myDrawLine(343.106,312.389,419.159,313.377);
    myDrawLine(344.833,318.869,426.325,319.992);
    myDrawLine(342.241,308.752,416.814,310.667);
    myDrawLine(340.152,301.5,407.588,301.946);
    myDrawLine(391,404.25,395.857,417.5);
    myDrawLine(409.901,404.25,415,417.5);
    myDrawLine(426.325,404.25,432.5,417.5);
    myDrawLine(377,371.063,381.133,380);
    myDrawLine(391,371.5,395.857,379.949);
    myDrawLine(407.588,371.5,412.451,379.949);
    myDrawLine(421.25,371.283,427.5,380);
    myDrawLine(436.25,371.5,441.5,380);
    myDrawLine(368.5,348.449,369.75,355.578);
    myDrawLine(381.133,349.09,383.791,355.578);
    myDrawLine(395.174,349.09,397.588,355.578);
    myDrawLine(407.588,349.09,410.02,355.578);
    myDrawLine(419.159,349.979,423.25,355.578);
    myDrawLine(431.241,349.979,436.25,355.578);
    myDrawLine(361.75,332.844,362.75,336.438);
    myDrawLine(373.677,332.308,375,336.438);
    myDrawLine(385.579,332.604,386.75,336.438);
    myDrawLine(396.695,332.844,397.588,336.438);
    myDrawLine(405.625,333.105,407.588,336.969);
    myDrawLine(419.159,333.442,421.205,336.438);
    myDrawLine(429.412,333.105,431.241,337.5);
    myDrawLine(355.729,318.869,357.436,322.446);
    myDrawLine(365.934,319.992,368.5,322.446);
    myDrawLine(377,319.992,377,323.375);
    myDrawLine(386.164,319.992,386.75,321.684);
    myDrawLine(396.695,319.992,398.615,323.591);
    myDrawLine(406.606,319.431,408.804,322.446);
    myDrawLine(415.887,319.431,418.909,321.791);
    myDrawLine(350.216,308.752,351.891,312.389);
    myDrawLine(360.064,309.71,361.75,310.571);
    myDrawLine(368.5,309.427,368.5,310.141);
    myDrawLine(373.87,310.571,375,310.667);
    myDrawLine(382.462,310.141,385.579,312.389);
    myDrawLine(388.713,310.571,391,311.265);
    myDrawLine(396.381,311.265,397.588,312.389);
    myDrawLine(402.125,310.141,403.717,311.265);
    myDrawLine(408.804,310.461,411.25,314.449);
    myDrawLine(343.106,304.834,407.588,306.187);
    myDrawLine(290.5,299.5,336,299.5);
    myDrawLine(290.5,301.5,334.75,301.946);
    myDrawLine(326,301.946,344.833,500);
    myDrawLine(313.25,301.946,307.75,500);
    myDrawLine(301.75,301.946,267.5,500);
    myDrawLine(229.5,500,386.75,500.231);
    myDrawLine(229.5,500,229.5,495.129);
    myDrawLine(247.878,436.791,370.852,437.975);
    myDrawLine(359.734,394.44,261.206,394.486);
    myDrawLine(270.5,364.985,352.488,366.067);
    myDrawLine(276.792,345.013,347.222,345.443);
    myDrawLine(281.803,329.107,343.15,329.5);
    myDrawLine(285.696,316.75,340.152,317.76);
    myDrawLine(288.551,307.688,337.852,308.752);
}
