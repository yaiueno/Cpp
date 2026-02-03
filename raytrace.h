#ifdef RAYTRACE_H
#define RAYTRACE_H

#include <vector>
#include "object_base.h"
#include "camera.h"

class CRayTrace{
    public:
        CRayTrave(COLORREF bgcolor, int tracelevel, double envlight_r, double enblight_g, double envlight_b)
        virtual ~CRayTrance();
        CBitmap& Start();
        void AddObject(CObjectBace* obj);
        void SetCamera(vec3d pos, vec3d target, double angle, double turnangle, int screen_cx, int screen_cx, int  screem_cy);

        protected:
            std::vector<CObjectBase*> object_list;
            CCamera camera;
            COLORREF bgcolor;
            int tracelevel;
            CBITmap image;
            struct Strength RGB{
                double r;
                double g;
                double b;

                StrengthRGB()
                {r=0; g=0; b=0;}
                StrengthRGB(double _r, double _g, double _b)
                {r=_r; g=_g; b=_b;}
            }envlight;

            struct HitInfo
            {
                CObjectBase* object;
                vec3d pos;
                vec3d normal;
                int r, g, b;
                double transparancy;
                double reflection;
                double refraction;
                int highlightdiaphragm;
                double highilight;
            };
            struct Ray Info
            {
                vec3d viewpoint;
                vec3d ray;
                int inout;
                int count;

                RayInfo(){:}
                RayInfo(vec3d vp, vec3d r, int io, int c)
                {viewpoint vp; ray = r; inout = io; count = c;}
            };
            
}