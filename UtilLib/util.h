/******************************************************************************

   REBVO: RealTime Edge Based Visual Odometry For a Monocular Camera.
   Copyright (C) 2016  Juan José Tarrio
   
   Jose Tarrio, J., & Pedre, S. (2015). Realtime Edge-Based Visual Odometry
   for a Monocular Camera. In Proceedings of the IEEE International Conference
   on Computer Vision (pp. 702-710).
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

 *******************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <TooN/TooN.h>
#include <stdio.h>

#include "timer.h"
#include "fvector.h"
namespace  rebvo{
namespace util{

    const double sqrt_2_pi=2.506628274631;
    const double num_inf=1e20;
    const double num_zero=1e-20;

    template <class T>
    inline int round2int_positive(T r){
        return (int)(r+0.5);
    }

    inline char clamp_char(float f){

        return f<-127?-127:f>128?128:f;
    }


    inline u_char clamp_uchar(float f){

        return f<0?0:f>255.0?255:f;
    }


    inline u_short clamp_ushort(float f){

        if(f<0)
            return 0;
        else if(f>65535.0)
            return 65535;
        else
            return (u_short)f;
    }

    inline short clamp_short(float f){

        if(f<-32768.0)
            return -32768;
        else if(f>32767.0)
            return 32767;
        else
            return (short)f;
    }

    template <typename T> T Constrain(const T &v,const T &min,const T &max){
        return v>max?max:(v<min?min:v);
    }

    template <class T,class T1> inline bool keep_min(T &t,T1 q){
	if(q<t){
	    t=q;
	    return true;
	}
	return false;
    }


    template <class T,class T1> inline bool keep_max(T &t,T1 q){
	if(q>t){
	    t=q;
	    return true;
	}
	return false;
    }

    template <class T,class T1> inline T saturate(T &t,T1 limit){
        return t>limit?limit:(t<-limit?-limit:t);
    }



    template <class T>
    inline T norm2(T a){
        return a*a;
    }

    template <class T>
    inline T norm2(T a,T b){
        return a*a+b*b;
    }
    template <class T>
    inline T norm2(T a,T b,T c){
        return a*a+b*b+c*c;
    }
    template <class T>
    inline double norm(T a,T b){
        return sqrt(norm2(a,b));
    }
    template <class T>
    inline double norm(T a,T b,T c){
        return sqrt(norm2(a,b,c));
    }

    template <class T>
    inline T square(T a){
        return a*a;
    }


    inline TooN::Matrix <3,3> Matrix3x3Inv(const TooN::Matrix <3,3> &A){
        TooN::Matrix <3,3> B;

        B(0,0)=  A(2,2)*A(1,1)-A(2,1)*A(1,2); B(0,1)=-(A(2,2)*A(0,1)-A(2,1)*A(0,2));B(0,2)=  A(1,2)*A(0,1)-A(1,1)*A(0,2);
        B(1,0)=-(A(2,2)*A(1,0)-A(2,0)*A(1,2));B(1,1)=  A(2,2)*A(0,0)-A(2,0)*A(0,2); B(1,2)=-(A(1,2)*A(0,0)-A(1,0)*A(0,2));
        B(2,0)=  A(2,1)*A(1,0)-A(2,0)*A(1,1); B(2,1)=-(A(2,1)*A(0,0)-A(2,0)*A(0,1));B(2,2)=  A(1,1)*A(0,0)-A(1,0)*A(0,1);


        return B/TooN::determinant(A);
    }



    template <int Ti,int Tj>
    inline bool isNaN(const TooN::Matrix<Ti,Tj> M){
        for(int i=0;i<Ti;i++)
            for(int j=0;j<Tj;j++)
                if(std::isnan(M(i,j)))
                    return true;
        return false;

    }
    template <int Ti>
    inline bool isNaN(const TooN::Vector<Ti> M){
        for(int i=0;i<Ti;i++)
                if(std::isnan(M[i]))
                    return true;
        return false;

    }

    inline TooN::Vector<4> LieRot2Quaternion(TooN::Vector<3>W){
        TooN::Vector<4> q;
        double angle=norm(W);
        if(angle>0)
            q.slice<0,3>()=W/angle*sin(angle/2);
        else
            q.slice<0,3>()=TooN::Zeros;
        q[3]=cos(angle/2);
        return q;
    }




}
}

#endif // UTIL_H
