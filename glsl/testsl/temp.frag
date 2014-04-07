//片段着色器temp.frag：
uniform vec3 CoolestColor;
uniform vec3 HottestColor;
varying float Temperature;
void main(void)
{
//通过温度值寻找一个相应的颜色，位于最冷和最热之间
vec3 color = mix(CoolestColor, HottestColor,Temperature);
gl_FragColor = vec4(color,1.0);
}
