/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkInformationVector.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkInformationVector
 * @brief   Store zero or more vtkInformation instances.
 *
 *
 * vtkInformationVector stores a vector of zero or more vtkInformation
 * objects corresponding to the input or output information for a
 * vtkAlgorithm.  An instance of this class is passed to
 * vtkAlgorithm::ProcessRequest calls.
 */

#ifndef vtkInformationVector_h
#define vtkInformationVector_h

#include "vtkCommonCoreModule.h" // For export macro
#include "vtkObject.h"

VTK_ABI_NAMESPACE_BEGIN
class vtkInformation;
class vtkInformationVectorInternals;

class VTKCOMMONCORE_EXPORT vtkInformationVector : public vtkObject
{
public:
  static vtkInformationVector* New();
  vtkTypeMacro(vtkInformationVector, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Get/Set the number of information objects in the vector.  Setting
   * the number to larger than the current number will create empty
   * vtkInformation instances.  Setting the number to smaller than the
   * current number will remove entries from higher indices.
   */
  int GetNumberOfInformationObjects() { return this->NumberOfInformationObjects; }
  void SetNumberOfInformationObjects(int n);
  ///@}

  ///@{
  /**
   * Get/Set the vtkInformation instance stored at the given index in
   * the vector.  The vector will automatically expand to include the
   * index given if necessary.  Missing entries in-between will be
   * filled with empty vtkInformation instances.
   */
  void SetInformationObject(int index, vtkInformation* info);
  vtkInformation* GetInformationObject(int index);
  ///@}

  ///@{
  /**
   * Append/Remove an information object.
   */
  void Append(vtkInformation* info);
  void Remove(vtkInformation* info);
  void Remove(int idx);
  ///@}

  ///@{
  /**
   * Initiate garbage collection when a reference is removed.
   */
  bool UsesGarbageCollector() const override { return true; }
  ///@}

  /**
   * Copy all information entries from the given vtkInformation
   * instance.  Any previously existing entries are removed.  If
   * deep==1, a deep copy of the information structure is performed (new
   * instances of any contained vtkInformation and vtkInformationVector
   * objects are created).
   */
  void Copy(vtkInformationVector* from, vtkTypeBool deep = 0);

protected:
  vtkInformationVector();
  ~vtkInformationVector() override;

  // Internal implementation details.
  vtkInformationVectorInternals* Internal;

  int NumberOfInformationObjects;

  // Garbage collection support.
  void ReportReferences(vtkGarbageCollector*) override;

private:
  vtkInformationVector(const vtkInformationVector&) = delete;
  void operator=(const vtkInformationVector&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif
