/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkWin32OpenGLImageWindow.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkWin32OpenGLImageWindow - OpenGL Imageing window
// .SECTION Description
// vtkWin32OpenGLImageWindow is a concrete implementation of the abstract
// class vtkImageWindow. vtkWin32OpenGLImageer interfaces to the standard
// OpenGL graphics library in the Windows/NT environment..

#ifndef __vtkWin32OpenGLImageWindow_h
#define __vtkWin32OpenGLImageWindow_h

#include <stdlib.h>
#include "vtkImageWindow.h"
#include "vtkMutexLock.h"

class VTK_RENDERING_EXPORT vtkWin32OpenGLImageWindow : public vtkImageWindow
{
public:
  static vtkWin32OpenGLImageWindow *New();
  vtkTypeRevisionMacro(vtkWin32OpenGLImageWindow,vtkImageWindow);
  void PrintSelf(ostream& os, vtkIndent indent);

  // output to the viewer.
  vtkWin32OpenGLImageWindow *GetOutput(){return this;};

  // Description:
  // Initialize the window for rendering.
  virtual void MakeDefaultWindow();

  // Description:
  // Swap the front and back buffers if double buffering is being used.
  void SwapBuffers();

  // Description:
  // Flush the buffer and swap if necessary
  void Frame();

  // Description:
  // Draw the contents of the window
  void Render();

  // Description:
  // Set the size of the window.
  virtual void SetSize(int,int);
  virtual void SetSize(int a[2]) {this->vtkImageWindow::SetSize(a);};

  // Description:
  // Get the current size of the window.
  virtual int *GetSize();
  virtual void GetSize(int *x, int *y) { this->vtkImageWindow::GetSize(x,y);};

  // Description:
  // Set the position of the window.
  virtual void SetPosition(int,int);
  virtual void SetPosition(int a[2]) {this->vtkImageWindow::SetPosition(a);};
  
  // Description:
  // Get the position in screen coordinates of the window.
  virtual int *GetPosition();
  virtual void GetPosition(int *x, int *y) { this->vtkImageWindow::GetPosition(x,y);};

  // Description:
  // Set the name of the window. This appears at the top of the window
  // normally.
  virtual void SetWindowName(char *);
  
  // Description:
  // Set this ImageWindow's window id to a pre-existing window.
  void SetWindowInfo(char *);

  // Description:
  // Sets the HWND id of the window that WILL BE created.
  void SetParentInfo(char *);

  //BTX
  virtual void *GetGenericDisplayId() {return (void *)this->ContextId;};
  virtual void *GetGenericWindowId()  {return (void *)this->WindowId;};
  virtual void *GetGenericParentId()  {return (void *)this->ParentId;};
  virtual void *GetGenericContext()   {return (void *)this->DeviceContext;};
  virtual void SetDisplayId(void *) {};

  // Description:
  // Get the window id.
  virtual HWND  GetWindowId();
  void  SetWindowId(void *foo) {this->SetWindowId((HWND)foo);};

  // Description:
  // Set the window id to a pre-existing window.
  virtual void  SetWindowId(HWND);
  
  // Description:
  // Set the window's parent id to a pre-existing window.
  virtual void  SetParentId(HWND);
  void  SetParentId(void *foo) {this->SetParentId((HWND)foo);};

  void  SetContextId(HGLRC);    // hsr
  void  SetDeviceContext(HDC);  // hsr

  // Description:
  // Set the window id of the new window once a WindowRemap is done.
  virtual void  SetNextWindowId(HWND);
  //ETX

  // Description:
  // Set/Get the pixel data of an image, transmitted as RGBRGB... 
  virtual unsigned char *GetPixelData(int x,int y,int x2,int y2,int front);
  virtual void SetPixelData(int x,int y,int x2,int y2,unsigned char *,
                            int front);

  // Description:
  // Set/Get the pixel data of an image, transmitted as RGBARGBA... 
  virtual float *GetRGBAPixelData(int x,int y,int x2,int y2,int front);
  virtual void SetRGBAPixelData(int x,int y,int x2,int y2,float *,int front,
                                int blend=0);
  virtual void ReleaseRGBAPixelData(float *data);

  // Description:
  // Make this windows OpenGL context the current context.
  void MakeCurrent();

  // Description:
  // These methods can be used by MFC applications 
  // to support print preview and printing, or more
  // general rendering into memory. 
  void SetupMemoryRendering(int x, int y, HDC prn);
  void ResumeScreenRendering();
  HDC GetMemoryDC();
  unsigned char *GetMemoryData(){return this->MemoryData;};  
  
  // Description:
  // Initialize OpenGL for this window.
  virtual void OpenGLInit();
  virtual void SetupPalette(HDC hDC);
  virtual void SetupPixelFormat(HDC hDC, DWORD dwFlags, int debug, 
                                int bpp=16, int zbpp=16);
  
  // Description:
  // Clean up device contexts, rendering contexts, etc.
  void Clean();

protected:
  vtkWin32OpenGLImageWindow();
  ~vtkWin32OpenGLImageWindow();

  HINSTANCE ApplicationInstance;
  HPALETTE  Palette;
  HPALETTE  OldPalette;
  HGLRC     ContextId;
  HDC       DeviceContext;
  HWND      WindowId;
  HWND      ParentId;
  HWND      NextWindowId;
  int       OwnWindow;
  int       ScreenSize[2];

  // the following is used to support rendering into memory
  BITMAPINFO MemoryDataHeader;
  HBITMAP MemoryBuffer;
  unsigned char *MemoryData;    // the data in the DIBSection
  HDC MemoryHdc;

  int ScreenMapped;
  int ScreenWindowSize[2];
  HDC ScreenDeviceContext;
  int ScreenDoubleBuffer;
  HGLRC ScreenContextId;

  //BTX
  // message handler
  virtual LRESULT MessageProc(HWND hWnd, UINT message, 
                              WPARAM wParam, LPARAM lParam);

  static LRESULT APIENTRY WndProc(HWND hWnd, UINT message, 
                                  WPARAM wParam, LPARAM lParam);
  //ETX
  
private:
  vtkWin32OpenGLImageWindow(const vtkWin32OpenGLImageWindow&);  // Not implemented.
  void operator=(const vtkWin32OpenGLImageWindow&);  // Not implemented.
};


#endif

