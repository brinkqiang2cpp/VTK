vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestDataObjectIO.cxx,NO_VALID
  TestIncrementalOctreePointLocator.cxx,NO_VALID
  UnstructuredGridCellGradients.cxx
  UnstructuredGridFastGradients.cxx
  UnstructuredGridGradients.cxx
  TestOBJPolyDataWriter.cxx
  TestOBJReaderComments.cxx,NO_VALID
  TestOBJReaderGroups.cxx,NO_VALID
  TestOBJReaderMaterials.cxx,NO_VALID
  TestOBJReaderMultiTexture.cxx,NO_VALID
  TestOBJReaderNormalsTCoords.cxx,NO_VALID
  TestOBJReaderRelative.cxx,NO_VALID
  TestOBJReaderSingleTexture.cxx,NO_VALID
  TestOpenFOAMReader.cxx
  TestOpenFOAMReader64BitFloats.cxx
  TestOpenFOAMReaderRegEx.cxx,NO_VALID
  TestProStarReader.cxx
  TestTecplotReader.cxx
  TestTecplotReader2.cxx,NO_VALID
  TestAMRReadWrite.cxx,NO_VALID
  TestSimplePointsReaderWriter.cxx,NO_VALID
  TestHoudiniPolyDataWriter.cxx,NO_VALID
  UnitTestSTLWriter.cxx,NO_VALID
  )

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestSTLReaderSinglePatch,TestSTLReader.cxx DATA{${_vtk_build_TEST_INPUT_DATA_DIRECTORY}/Data/42400-IDGH.stl}
)

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestSTLReaderMultiplePatches,TestSTLReader.cxx DATA{${_vtk_build_TEST_INPUT_DATA_DIRECTORY}/Data/multiple_patches.stl}
)

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestPTSReader,TestPTSReader.cxx DATA{${_vtk_build_TEST_INPUT_DATA_DIRECTORY}/Data/samplePTS.pts}
)

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestAVSucdReaderContiguousASCII,TestAVSucdReader.cxx DATA{${_vtk_build_TEST_INPUT_DATA_DIRECTORY}/Data/cellsnd.ascii.inp}
)
vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestAVSucdReaderNonContiguousASCII,TestAVSucdReader.cxx DATA{${_vtk_build_TEST_INPUT_DATA_DIRECTORY}/Data/cellsnd.noncontiguous.ascii.inp}
)
vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestAVSucdReaderBinary,TestAVSucdReader.cxx DATA{${_vtk_build_TEST_INPUT_DATA_DIRECTORY}/Data/cellsnd.bin.inp}
)

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestGLTFReaderGeometry,TestGLTFReaderGeometry.cxx DATA{../Data/glTF/Triangle/Triangle.gltf,simpleTriangle.bin}
)

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestGLTFReaderEmbeddedGeometry,TestGLTFReaderGeometry.cxx DATA{../Data/glTF/Triangle/EmbeddedTriangle.gltf}
)

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestGLTFReaderGLBGeometry,TestGLTFReaderGeometry.cxx DATA{../Data/glTF/Triangle/Triangle.glb}
)

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestGLTFReaderAnimation,TestGLTFReaderAnimation.cxx 200 DATA{../Data/glTF/BoxAnimated/BoxAnimated.gltf,BoxAnimated0.bin}
)

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestGLTFReaderMorphing,TestGLTFReaderAnimation.cxx 200 DATA{../Data/glTF/AnimatedMorphCube/AnimatedMorphCube.gltf,AnimatedMorphCube.bin}
)

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestGLTFReaderSkinning,TestGLTFReaderAnimation.cxx 200 DATA{../Data/glTF/SimpleSkin/SimpleSkin.gltf}
)

vtk_add_test_cxx(vtkIOGeometryCxxTests tests
  TestGLTFReaderMultipleAnimations,TestGLTFReaderAnimation.cxx 75 DATA{../Data/glTF/InterpolationTest/InterpolationTest.gltf,interpolation.bin,InterpolationTest_data.bin}
)

if(enable_large_data_tests)
  vtk_add_test_cxx(vtkIOGeometryCxxTests large_data_tests
    TestWindBladeReader.cxx
    TestMFIXReader.cxx,NO_VALID
    )
  list(APPEND tests
    ${large_data_tests}
    )
endif()

vtk_test_cxx_executable(vtkIOGeometryCxxTests tests)
