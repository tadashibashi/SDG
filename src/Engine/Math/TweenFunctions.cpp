/**
Terms of Use: Easing Functions (Equations)
Open source under the MIT License and the 3-Clause BSD License.
MIT License
Copyright © 2001 Robert Penner
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
BSD License
Copyright © 2001 Robert Penner
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
Neither the name of the author nor the names of contributors may be used to
endorse or promote products derived from this software without specific
prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/
#include "TweenFunctions.h"
#include <cmath>

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const float BackConst = 1.70158f;

float
SDG::TweenF::Linear(float currentTime, float start, float relTarget, float duration)
{
    return relTarget * currentTime / duration + start;
}

float
SDG::TweenF::EaseInQuad(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration;
    return relTarget * currentTime * currentTime + start;
}

float
SDG::TweenF::EaseOutQuad(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration;
    return -relTarget * currentTime * (currentTime - 2) + start;
}

float
SDG::TweenF::EaseInOutQuad(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration / 2;
    if (currentTime < 1.f)
    {
        return relTarget / 2 * currentTime * currentTime + start;
    }
    else
    {
        currentTime--;
        return -relTarget / 2 * (currentTime*(currentTime-2) - 1) + start;
    }
}

float
SDG::TweenF::EaseInCubic(float currentTime, float start, float relTarget, float duration) {
    currentTime /= duration;
    return relTarget * currentTime * currentTime * currentTime + start;
}

float
SDG::TweenF::EaseOutCubic(float currentTime, float start, float relTarget, float duration)
{
    currentTime = currentTime/duration - 1;
    return relTarget * (currentTime * currentTime * currentTime + 1) + start;
}

float
SDG::TweenF::EaseInOutCubic(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration/2.f;
    if (currentTime < 1.f)
    {
        return relTarget / 2.f * currentTime * currentTime * currentTime + start;
    }
    else
    {
        currentTime -= 2.f;
        return relTarget/2.f * (currentTime * currentTime * currentTime + 2.f) + start;
    }
}

float
SDG::TweenF::EaseInSine(float currentTime, float start, float relTarget, float duration)
{
    return -relTarget * cos(currentTime/duration * ((float)M_PI /2.f)) + relTarget + start;
}

float
SDG::TweenF::EaseOutSine(float currentTime, float start, float relTarget, float duration)
{
    return relTarget * sin(currentTime / duration * ((float)M_PI/2.f)) + start;
}

float
SDG::TweenF::EaseInOutSine(float currentTime, float start, float relTarget, float duration)
{
    return -relTarget/2.f * (cos((float)M_PI*currentTime/duration) - 1.f) + start;
}

float
SDG::TweenF::EaseInBack(float currentTime, float start, float relTarget, float duration)
{
    float postfix = currentTime /= duration;
    return relTarget * postfix * currentTime * ((BackConst + 1) * currentTime - BackConst) + start;
}

float
SDG::TweenF::EaseOutBack(float currentTime, float start, float relTarget, float duration)
{
    return relTarget * ((currentTime = currentTime/duration-1.f) * currentTime *
        ((BackConst + 1.f) * currentTime + BackConst) + 1.f) + start;
}

float
SDG::TweenF::EaseInOutBack(float currentTime, float start, float relTarget, float duration)
{
    float s = BackConst;
    if ((currentTime /= duration / 2.f) < 1) return relTarget / 2.f * (currentTime * currentTime *
        (((s *= 1.525f) + 1.f) * currentTime + s)) + start;
    float postfix = currentTime -= 2.f;
    return relTarget / 2.f * (postfix * currentTime * (((s *= 1.525f)+1.f) *currentTime + s) + 2.f) + start;
}

float
SDG::TweenF::EaseInQuart(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration;
    return relTarget * currentTime * currentTime * currentTime * currentTime + start;
}

float
SDG::TweenF::EaseOutQuart(float currentTime, float start, float relTarget, float duration)
{
    currentTime = currentTime/duration - 1;
    return -relTarget * (currentTime * currentTime * currentTime * currentTime - 1) + start;
}

float
SDG::TweenF::EaseInOutQuart(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration / 2.f;
    if (currentTime < 1.f) return relTarget / 2.f * currentTime * currentTime * currentTime * currentTime + start;
    currentTime -= 2.f;
    return -relTarget/2.f * (currentTime * currentTime * currentTime * currentTime - 2.f) + start;
}

float
SDG::TweenF::EaseInQuint(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration;
    return relTarget * currentTime * currentTime * currentTime * currentTime * currentTime + start;
}

float
SDG::TweenF::EaseOutQuint(float currentTime, float start, float relTarget, float duration)
{
    currentTime = currentTime/duration - 1;
    return -relTarget * (currentTime * currentTime * currentTime * currentTime * currentTime + 1) + start;
}

float
SDG::TweenF::EaseInOutQuint(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration / 2.f;
    if (currentTime < 1.f) return relTarget / 2.f * currentTime * currentTime * currentTime * currentTime * currentTime + start;
    currentTime -= 2.f;
    return -relTarget/2.f * (currentTime * currentTime * currentTime * currentTime * currentTime + 2.f) + start;
}

float
SDG::TweenF::EaseInExpo(float currentTime, float start, float relTarget, float duration)
{
    return relTarget * pow(2.f, 10.f * (currentTime/duration - 1.f)) + start;
}

float
SDG::TweenF::EaseOutExpo(float currentTime, float start, float relTarget, float duration)
{
    return relTarget * (-pow(2.f, -10.f * currentTime / duration) + 1.f) + start;
}

float
SDG::TweenF::EaseInOutExpo(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration /2.f;
    if (currentTime < 1.f) return relTarget / 2.f * pow(2.f, 10.f * (currentTime - 1.f)) + start;
    --currentTime;
    return relTarget / 2.f * (-pow(2.f, -10.f * currentTime) + 2.f) + start;
}

float
SDG::TweenF::EaseInCirc(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration;
    return -relTarget * (sqrt(1.f - currentTime * currentTime) - 1.f ) + start;
}

float
SDG::TweenF::EaseOutCirc(float currentTime, float start, float relTarget, float duration)
{
    currentTime = currentTime / duration - 1.f;
    return relTarget * sqrt(1.f - currentTime * currentTime) + start;
}

float
SDG::TweenF::EaseInOutCirc(float currentTime, float start, float relTarget, float duration)
{
    currentTime /= duration /2.f;
    if (currentTime < 1.f) return -relTarget / 2.f * (sqrt(1.f - currentTime * currentTime) -1.f) + start;
    currentTime -= 2.f;
    return relTarget / 2.f * (sqrt(1.f - currentTime * currentTime) + 1.f) + start;
}

float
SDG::TweenF::EaseInBounce(float currentTime, float start, float relTarget, float duration)
{
    return relTarget - EaseOutBounce(duration-currentTime, 0, relTarget, duration) + start;
}

float
SDG::TweenF::EaseOutBounce(float currentTime, float start, float relTarget, float duration)
{
    if ((currentTime /= duration) < 1.f/2.75f)
        return relTarget * (7.5625f * currentTime * currentTime) + start;
    else if (currentTime < (2.f/2.75f))
    {
        float postfix = (currentTime -= (1.5f / 2.75f));
        return relTarget * (7.5625f * postfix * currentTime + .75f) + start;
    }
    else if (currentTime < 2.5f/2.75f)
    {
        float postfix = (currentTime -= (2.75f/2.75f));
        return relTarget * (7.5625f * postfix * currentTime + .9375f) + start;
    }
    else
    {
        float postfix = (currentTime -= (2.625f / 2.75f));
        return relTarget * (7.5625f * postfix * currentTime + .984375f) + start;
    }
}

float
SDG::TweenF::EaseInOutBounce(float currentTime, float start, float relTarget, float duration)
{
    return (currentTime < duration / 2.f) ?
        EaseInBounce(currentTime * 2.f, 0, relTarget, duration) * .5f + start :
        EaseOutBounce(currentTime * 2.f - duration, 0, relTarget, duration) * .5f + relTarget * .5f + start;
}
