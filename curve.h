//
//  curve.h
//  fractal_dragon_curve
//
//  Created by mb9 on 22/11/2020.
//

#ifndef curve_h
#define curve_h

class Curve
{
public:
    ofVec2f pts[2];
    Curve* next;
    
    Curve(ofVec2f p1, ofVec2f p2)
    {
        pts[0] = p1;
        pts[1] = p2;
        next = NULL;
    }
    
    void addVertices()
    {
        glVertex2f(pts[0].x, pts[0].y);
        glVertex2f(pts[1].x, pts[1].y);
    }
    
    void split(float angle, float split_fraction)
    {
        if(ofDist(pts[0].x, pts[0].y, pts[1].x, pts[1].y) > 4)
        {
            ofVec2f newPt = pts[1] - pts[0];
            newPt.rotate(angle);
    //        newPt /= sqrt(2);
            newPt /= split_fraction;
            newPt += pts[0];
            
            Curve* newCurve = new Curve(newPt, pts[1]);
            pts[1] = newPt;
            
            newCurve->next = next;
            next = newCurve;
        }
    }
    
    void draw()
    {
        ofDrawLine(pts[0], pts[1]);
    }
};


#endif /* curve_h */
