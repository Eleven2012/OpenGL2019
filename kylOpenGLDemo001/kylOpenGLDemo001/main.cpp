//
//  main.cpp
//  kylOpenGLDemo001
//
//  Created by 孔雨露 on 2019/12/7.
//  Copyright © 2019 Apple. All rights reserved.
//

//移入了GLTool 着色器管理器（shader Mananger）类。没有着色器，我们就不能在OpenGL（核心框架）进行着色。着色器管理器不仅允许我们创建并管理着色器，还提供一组“存储着色器”，他们能够进行一些初步䄦基本的渲染操作。


#include "GLShaderManager.h"

// GLTool.h头文件包含了大部分GLTool中类似C语言的独立函数
#include "GLTools.h"

#include <glut/glut.h> //MAC使用的库
//在Windows 和 Linux上，我们使用freeglut的静态库版本并且需要添加一个宏。
//#define FREEGLUT_STATIC
//#include<GL/glut.h>

GLBatch triangleBatch;

GLShaderManager shaderManager;

//窗口大小改变时接受新的宽度和高度，其中0,0代表窗口中视口的左下角坐标，w，h代表像素

void ChangeSize(int w,int h)

{
    
    glViewport(0,0, w, h);
    
}

//为程序作一次性的设置

void SetupRC()

{
    
    //设置背影颜色
    
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    
    //初始化着色管理器
    
    shaderManager.InitializeStockShaders();
    
    //设置三角形，其中数组vVert包含所有3个顶点的x,y,笛卡尔坐标对。
    
    GLfloat vVerts[] = {
        
        -0.5f,0.0f,0.0f,
        
        0.5f,0.0f,0.0f,
        
        0.0f,0.5f,0.0f,
        
    };
    
    //批次处理
    
    triangleBatch.Begin(GL_TRIANGLES,3);
    
    triangleBatch.CopyVertexData3f(vVerts);
    
    triangleBatch.End();
    
}

//开始渲染

void RenderScene(void)

{
    
    //清除一个或一组特定的缓冲区
  //缓冲区是一块存在图像信息的储存空间，红色、绿色、蓝色和alpha分量通常一起分量通常一起作为颜色缓存区或像素缓存区引用。
    //OpenGL 中不止一种缓冲区（颜色缓存区、深度缓存区和模板缓存区）。
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    
    //设置一组浮点数来表示红色
    
    GLfloat vRed[] = {1.0f,0.0f,0.0f,1.0f};
    
    //传递到存储着色器，即GLT_SHADER_IDENTITY着色器，这个着色器只是使用指定颜色以默认笛卡尔坐标第在屏幕上渲染几何图形
    //没有着色器，在OpenGL 核心框架中就无法进行任何渲染。在后面的课程中我们讲到不用固定渲染管线，当然在前期会先学习如果使用存储着色器。
    
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
    
    //提交着色器
    
    triangleBatch.Draw();
    
    //将在后台缓冲区进行渲染，然后在结束时交换到前台
    
    glutSwapBuffers();
    
}

int main(int argc,char* argv[])

{
    
    //设置当前工作目录，针对MAC OS X
    /*
        `GLTools`函数`glSetWorkingDrectory`用来设置当前工作目录。实际上在Windows中是不必要的，因为工作目录默认就是与程序可执行执行程序相同的目录。但是在Mac OS X中，这个程序将当前工作文件夹改为应用程序捆绑包中的`/Resource`文件夹。`GLUT`的优先设定自动进行了这个中设置，但是这样中方法更加安全。
        */

    gltSetWorkingDirectory(argv[0]);
    
    //初始化GLUT库
  //负责初始化GLUT库。它会处理向程序输入的命令行参数，并且移除其中与控制GLUT如何操作相关的部分。它必须是应用程序第一个GLUT函数，负责设置其他GLUT例程必需的数据结构。

    glutInit(&argc, argv);
    
    /*初始化双缓冲窗口，其中标志GLUT_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL分别指
     
     双缓冲窗口、RGBA颜色模式、深度测试、模板缓冲区
     
     glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    GLUT_DOUBLE：双缓存窗口，是指绘图命令实际上是离屏缓存区执行的，然后迅速转换成窗口视图，这种方式，经常用来生成动画效果；
     GLUT_DEPTH：标志将一个深度缓存区分配为显示的一部分，因此我们能够执行深度测试；
     GLUT_STENCIL：确保我们也会有一个可用的模板缓存区。

     */
    //创建窗口并设置显示模式
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    
    //GLUT窗口大小，标题窗口
    //glutInitWindowSize设置所需的窗口大小，如果不想在这个设置一个固定值，也可以先查询显示设备的尺寸，然后根据计算机的屏幕动态设置窗口的大小。

    glutInitWindowSize(800,600);
    //glutCreateWindow它的功能和它的名字一样，如果当前的系统环境可以满足glutInitDisplayMode()的显示模式要求，这里就会创建一个窗口（此时会调用计算机窗口系统的接口）。只有GLUT创建了一个窗口之后（其中包含创建创建OpenGL环境的过程），我们才可以使用OpenGL相关的函数

    glutCreateWindow("kongyulu first opengl demo");
    
    //注册回调函数
    
    glutReshapeFunc(ChangeSize);
    
    //它设置了一个显示回调（diplay callback），即GLUT在每次更新窗口内容的时候回自动调用该例程
    glutDisplayFunc(RenderScene);
    
    //驱动程序的初始化中没有出现任何问题。
    //glewInit函数，属于另一个辅助库GLEW（OpenGL Extention Wrangler）。GLEW可以简化获取函数地址的过程，并且包含了可以跨平台使用的其他一些OpenGL编程方法。

    GLenum err = glewInit();
    
    if(GLEW_OK != err) {
        
        fprintf(stderr,"glew error:%s\n",glewGetErrorString(err));
        
        return 1;
        
    }
    
    //调用SetupRC
    
    SetupRC();
    
    //glutMainLoop这是一个无限执行的循环，它会负责一直处理窗口和操作系统的用户输入等操作。（注意：不会执行在glutMainLoop()之后的所有命令。）

    glutMainLoop();
    
    return 0;
    
}

