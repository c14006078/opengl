//先看顶点着色器temp.vert：
uniform float CoolestTemp;
uniform float TempRange;
attribute float VertexTemp;//每个定点都对应一个温度值
varying float Temperature;//传递到片段处理器进行后续处理
void main(void)
{
 //进行插值
Temperature = (VertexTemp - CoolestTemp) / TempRange;
gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
