/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkVolumeMapper.cxx
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
#include "vtkVolumeMapper.h"
#include "vtkImageClip.h"

vtkCxxRevisionMacro(vtkVolumeMapper, "1.37");

// Construct a vtkVolumeMapper with empty scalar input and clipping off.
vtkVolumeMapper::vtkVolumeMapper()
{
  int i;

  this->Cropping = 0;
  for ( i = 0; i < 3; i++ )
    {
    this->CroppingRegionPlanes[2*i    ]      = 0;
    this->CroppingRegionPlanes[2*i + 1]      = 1;
    this->VoxelCroppingRegionPlanes[2*i]     = 0;
    this->VoxelCroppingRegionPlanes[2*i + 1] = 1;    
    }
  this->Bounds[0] = this->Bounds[2] = this->Bounds[4] = -1.0;
  this->Bounds[1] = this->Bounds[3] = this->Bounds[5] = 1.0;
  this->Center[0] = this->Center[1] = this->Center[2] = 0.0;
  this->CroppingRegionFlags = 0x02000;
  
  this->ImageClipper = vtkImageClip::New();
  this->ImageClipper->ClipDataOn();
}

vtkVolumeMapper::~vtkVolumeMapper()
{
  
  this->ImageClipper->Delete();
}

void vtkVolumeMapper::Update()
{
  if ( this->GetInput() )
    {
    this->GetInput()->UpdateInformation();
    this->GetInput()->SetUpdateExtentToWholeExtent();
    this->GetInput()->Update();
    }

  if ( this->GetRGBTextureInput() )
    {
    this->GetRGBTextureInput()->UpdateInformation();
    this->GetRGBTextureInput()->SetUpdateExtentToWholeExtent();
    this->GetRGBTextureInput()->RequestExactExtentOn();
    this->GetRGBTextureInput()->Update();
    }
}

void vtkVolumeMapper::ConvertCroppingRegionPlanesToVoxels()
{
  float *spacing    = this->GetInput()->GetSpacing();
  float *origin     = this->GetInput()->GetOrigin();
  int   *dimensions = this->GetInput()->GetDimensions();
  
  for ( int i = 0; i < 6; i++ )
    {
    this->VoxelCroppingRegionPlanes[i] =
      (this->CroppingRegionPlanes[i] - origin[i/2]) / spacing[i/2];
    
    this->VoxelCroppingRegionPlanes[i] = 
      ( this->VoxelCroppingRegionPlanes[i] < 0 ) ?
      ( 0 ) : ( this->VoxelCroppingRegionPlanes[i] );

    this->VoxelCroppingRegionPlanes[i] = 
      ( this->VoxelCroppingRegionPlanes[i] > dimensions[i/2]-1 ) ?
      ( dimensions[i/2]-1 ) : ( this->VoxelCroppingRegionPlanes[i] );
    }
}

// Get the bounds for the input of this mapper as 
// (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
float *vtkVolumeMapper::GetBounds()
{
  static float bounds[] = {-1.0,1.0, -1.0,1.0, -1.0,1.0};

  if ( ! this->GetInput() ) 
    {
    return bounds;
    }
  else
    {
    this->GetInput()->UpdateInformation();
    this->GetInput()->SetUpdateExtentToWholeExtent();
    this->GetInput()->Update();
    this->GetInput()->GetBounds(this->Bounds);
    return this->Bounds;
    }
}

void vtkVolumeMapper::SetInput( vtkImageData *input )
{
  this->ImageClipper->SetInput( input );
  this->vtkProcessObject::SetNthInput(0, this->ImageClipper->GetOutput() );
}

vtkImageData *vtkVolumeMapper::GetInput()
{
  if (this->NumberOfInputs < 1)
    {
    return NULL;
    }
  return (vtkImageData*)(this->Inputs[0]);
}


void vtkVolumeMapper::SetRGBTextureInput( vtkImageData *rgbTexture )
{
  vtkPointData    *pd;
  vtkDataArray    *scalars;

  if ( rgbTexture )
    {
    rgbTexture->UpdateInformation();
    rgbTexture->SetUpdateExtentToWholeExtent();
    rgbTexture->Update();
    pd = rgbTexture->GetPointData();
    if ( !pd )
      {
      vtkErrorMacro( << "No PointData in texture!" );
      return;
      }
    scalars = pd->GetScalars();
    if ( !scalars )
      {
      vtkErrorMacro( << "No scalars in texture!" );
      return;
      }
    if ( scalars->GetDataType() != VTK_UNSIGNED_CHAR )
      {
      vtkErrorMacro( << "Scalars in texture must be unsigned char!" );
      return;      
      }
    if ( scalars->GetNumberOfComponents() != 3 )
      {
      vtkErrorMacro( << "Scalars must have 3 components (r, g, and b)" );
      return;      
      }
    }
  
  this->vtkProcessObject::SetNthInput(1, rgbTexture);

}

vtkImageData *vtkVolumeMapper::GetRGBTextureInput()
{
  if (this->NumberOfInputs < 2)
    {
    return NULL;
    }
  return (vtkImageData *)(this->Inputs[1]);
}


// Print the vtkVolumeMapper
void vtkVolumeMapper::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  if ( this->GetRGBTextureInput() )
    {
    os << indent << "RGBTextureInput: (" << this->GetRGBTextureInput() 
       << ")\n";
    }
  else
    {
    os << indent << "RGBTextureInput: (none)\n";
    }

  os << indent << "Cropping: " << (this->Cropping ? "On\n" : "Off\n");

  os << indent << "Cropping Region Planes: " << endl 
     << indent << "  In X: " << this->CroppingRegionPlanes[0] 
     << " to " << this->CroppingRegionPlanes[1] << endl 
     << indent << "  In Y: " << this->CroppingRegionPlanes[2] 
     << " to " << this->CroppingRegionPlanes[3] << endl 
     << indent << "  In Z: " << this->CroppingRegionPlanes[4] 
     << " to " << this->CroppingRegionPlanes[5] << endl;
 
  os << indent << "Cropping Region Flags: " 
     << this->CroppingRegionFlags << endl;

  // Don't print this->VoxelCroppingRegionPlanes
  
  os << indent << "Build Time: " <<this->BuildTime.GetMTime() << "\n";
}

