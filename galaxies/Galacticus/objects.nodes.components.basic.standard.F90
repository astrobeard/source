!! Copyright 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018
!!    Andrew Benson <abenson@carnegiescience.edu>
!!
!! This file is part of Galacticus.
!!
!!    Galacticus is free software: you can redistribute it and/or modify
!!    it under the terms of the GNU General Public License as published by
!!    the Free Software Foundation, either version 3 of the License, or
!!    (at your option) any later version.
!!
!!    Galacticus is distributed in the hope that it will be useful,
!!    but WITHOUT ANY WARRANTY; without even the implied warranty of
!!    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!!    GNU General Public License for more details.
!!
!!    You should have received a copy of the GNU General Public License
!!    along with Galacticus.  If not, see <http://www.gnu.org/licenses/>.

!% Contains a module with the standard implementation of basic tree node methods.

module Node_Component_Basic_Standard
  !% The standard implementation of basic tree node methods.
  use Galacticus_Nodes
  implicit none
  private
  public :: Node_Component_Basic_Standard_Rate_Compute   , Node_Component_Basic_Standard_Scale_Set     , &
       &    Node_Component_Basic_Standard_Tree_Initialize, Node_Component_Basic_Standard_Stop_Accretion, &
       &    Node_Component_Basic_Standard_Promote        , Node_Component_Basic_Standard_Plausibility

  !# <component>
  !#  <class>basic</class>
  !#  <name>standard</name>
  !#  <isDefault>true</isDefault>
  !#  <properties>
  !#   <property>
  !#     <name>mass</name>
  !#     <type>double</type>
  !#     <rank>0</rank>
  !#     <attributes isSettable="true" isGettable="true" isEvolvable="true" />
  !#     <output unitsInSI="massSolar" comment="Total mass of the node, assuming universal baryon fraction."/>
  !#   </property>
  !#   <property>
  !#     <name>time</name>
  !#     <type>double</type>
  !#     <rank>0</rank>
  !#     <attributes isSettable="true" isGettable="true" isEvolvable="true" />
  !#   </property>
  !#   <property>
  !#     <name>timeLastIsolated</name>
  !#     <type>double</type>
  !#     <rank>0</rank>
  !#     <attributes isSettable="true" isGettable="true" isEvolvable="false" />
  !#     <getFunction bindsTo="component">BasicStandardTimeLastIsolated</getFunction>
  !#     <output unitsInSI="gigaYear" comment="Time at which node was last an isolated halo."/>
  !#   </property>
  !#   <property>
  !#     <name>accretionRate</name>
  !#     <type>double</type>
  !#     <rank>0</rank>
  !#     <attributes isSettable="true" isGettable="true" isEvolvable="false" />
  !#   </property>
  !#  </properties>
  !#  <functions>objects.nodes.components.basic.standard.bound_functions.inc</functions>
  !# </component>

contains

  !# <rateComputeTask>
  !#  <unitName>Node_Component_Basic_Standard_Rate_Compute</unitName>
  !# </rateComputeTask>
  subroutine Node_Component_Basic_Standard_Rate_Compute(node,odeConverged,interrupt,interruptProcedure,propertyType)
    !% Compute rates of change of properties in the standard implementation of the basic component.
    implicit none
    type     (treeNode          ), intent(inout), pointer :: node
    logical                      , intent(in   )          :: odeConverged
    logical                      , intent(inout)          :: interrupt
    procedure(                  ), intent(inout), pointer :: interruptProcedure
    integer                      , intent(in   )          :: propertyType
    class    (nodeComponentBasic)               , pointer :: basicComponent
    !GCC$ attributes unused :: interrupt, interruptProcedure, odeConverged
    
    ! Return immediately if inactive variables are requested.
    if (propertyType == propertyTypeInactive) return
    ! Get the basic component.
    basicComponent => node%basic()
    ! Ensure that it is of the standard class.
    select type (basicComponent)
    class is (nodeComponentBasicStandard)
       ! Mass rate of change is set to the accretion rate.
       call basicComponent%massRate(basicComponent%accretionRate())
       ! Time rate of change is unity, by definition.
       call basicComponent%timeRate(1.0d0                         )
    end select
    return
  end subroutine Node_Component_Basic_Standard_Rate_Compute

  !# <scaleSetTask>
  !#  <unitName>Node_Component_Basic_Standard_Scale_Set</unitName>
  !# </scaleSetTask>
  subroutine Node_Component_Basic_Standard_Scale_Set(node)
    !% Set scales for properties in the standard implementation of the basic component.
    implicit none
    type            (treeNode          ), intent(inout), pointer :: node
    double precision                    , parameter              :: timeScale        =1.0d-3
    double precision                    , parameter              :: scaleMassRelative=1.0d-6
    class           (nodeComponentBasic)               , pointer :: basicComponent

    ! Get the basic component.
    basicComponent => node%basic()
    ! Ensure that it is of the standard class.
    select type (basicComponent)
    class is (nodeComponentBasicStandard)
       ! Set scale for time.
       call basicComponent%timeScale(timeScale                              )
       ! Set scale for mass.
       call basicComponent%massScale(basicComponent%mass()*scaleMassRelative)
    end select
    return
  end subroutine Node_Component_Basic_Standard_Scale_Set

  !# <mergerTreeInitializeTask>
  !#  <unitName>Node_Component_Basic_Standard_Tree_Initialize</unitName>
  !# </mergerTreeInitializeTask>
  subroutine Node_Component_Basic_Standard_Tree_Initialize(node)
    !% Set the mass accretion rate for {\normalfont \ttfamily node}.
    implicit none
    type            (treeNode          ), intent(inout), pointer :: node
    type            (treeNode          )               , pointer :: childNode          , nodeParent
    class           (nodeComponentBasic)               , pointer :: childBasicComponent, basicParent, basic
    double precision                                             :: deltaTime          , massUnresolved      , progenitorMassTotal

    ! Get the basic component.
    basic => node%basic()
    ! Ensure that it is of the standard class.
    select type (basic)
    class is (nodeComponentBasicStandard)
       ! Set the last isolated time to the current time at the farthest point along the future of this branch.
       nodeParent => node
       do while (associated(nodeParent%parent).and.nodeParent%isPrimaryProgenitor())
          nodeParent => nodeParent%parent
       end do
       basicParent => nodeParent%basic()
       call basic%timeLastIsolatedSet(basicParent%time())
       ! Determine node status.
       if (node%isSatellite()) then
          ! Node is a satellite - we assume no accretion.
          call basic%accretionRateSet(0.0d0)
       else if (.not.associated(node%parent)) then
          ! For parent-less nodes (i.e. the root node of the tree), the rate is set equal to that of the
          ! progenitor, if it has one.
          childNode => node%firstChild
          if (associated(childNode)) then
             ! Get the basic component of the child node.
             childBasicComponent => childNode%basic()
             ! Ensure the child has a mass growth rate computed.
             call Node_Component_Basic_Standard_Tree_Initialize(childNode)
             ! Get the growth rate of the child.
             call basic%accretionRateSet(childBasicComponent%accretionRate())
          else
             ! Parentless node has no child - set a zero growth rate.
             call basic%accretionRateSet(0.0d0                              )
          end if
       else
          ! Get the parent node.
          nodeParent => node%parent
          ! Get the basic component of the parent node.
          basicParent => nodeParent%basic()
          ! Compute the unresolved mass.
          massUnresolved=Node_Component_Basic_Standard_Unresolved_Mass(nodeParent)
          if (massUnresolved > 0.0d0) then
             ! Positive mass growth - assume this occurs entirely in the main progenitor.
             if (node%isPrimaryProgenitor()) then
                ! Main progenitor - compute required growth rate.
                deltaTime=basicParent%time()-basic%time()
                if (deltaTime > 0.0d0) call basic%accretionRateSet(massUnresolved/deltaTime)
             else
                ! Non-main progenitor - assume zero growth rate.
                call basic%accretionRateSet(0.0d0)
             end if
          else
             ! Negative mass growth - assume all progenitors lose mass at proportionally equal rates.
             ! Compute the total mass in progenitors.
             progenitorMassTotal=basicParent%mass()-massUnresolved
             ! Compute the time available for accretion.
             deltaTime=basicParent%time()-basic%time()
             ! Compute mass growth rate.
             if (deltaTime > 0.0d0) call basic%accretionRateSet((massUnresolved/deltaTime)*(basic%mass()/progenitorMassTotal))
          end if
       end if
    end select
    return
  end subroutine Node_Component_Basic_Standard_Tree_Initialize

  !# <nodeMergerTask>
  !#  <unitName>Node_Component_Basic_Standard_Stop_Accretion</unitName>
  !# </nodeMergerTask>
  subroutine Node_Component_Basic_Standard_Stop_Accretion(node)
    !% Switch off accretion of new mass onto this node once it becomes a satellite.
    implicit none
    type (treeNode          ), intent(inout), pointer :: node
    class(nodeComponentBasic)               , pointer :: basic

    ! Get the basic component.
    basic => node%basic()
    ! Ensure that it is of the standard class.
    select type (basic)
    class is (nodeComponentBasicStandard)
       ! Shut down mass accretion onto the halo now that it is a satellite.
       call basic%accretionRateSet   (0.0d0       )
       ! Record the time at which the node became a satellite - used for computing halo scales etc.
       call basic%timeLastIsolatedSet(basic%time())
    end select
    return
  end subroutine Node_Component_Basic_Standard_Stop_Accretion

   !# <nodePromotionTask>
   !#  <unitName>Node_Component_Basic_Standard_Promote</unitName>
   !# </nodePromotionTask>
   subroutine Node_Component_Basic_Standard_Promote(node)
     !% Ensure that {\normalfont \ttfamily node} is ready for promotion to its parent. In this case, we simply update the mass of {\normalfont \ttfamily node}
     !% to be that of its parent.
     use Galacticus_Error
     use ISO_Varying_String
     use String_Handling
     implicit none
     type     (treeNode          ), intent(inout), pointer :: node
     type     (treeNode          )               , pointer :: nodeParent
     class    (nodeComponentBasic)               , pointer :: basicParent, basic
     type     (varying_string    )                         :: message
     character(len=12            )                         :: label
     
     ! Get the basic component.
     basic => node%basic()
     ! Ensure that it is of the standard class.
     select type (basic)
     class is (nodeComponentBasicStandard)
        ! Get the parent node and its basic component.
        nodeParent           => node  %parent
        basicParent => nodeParent%basic()
        ! Ensure the two halos exist at the same time.
        if (basic%time() /= basicParent%time()) then
           message=var_str("node [")//node%index()//"] has not been evolved to its parent ["//nodeParent%index()//"]"//char(10)
           write (label,'(f12.6)') basic%time()
           message=message//"    node is at time: "//label//" Gyr"//char(10)
           write (label,'(f12.6)') basicParent%time()
           message=message//"  parent is at time: "//label//" Gyr"
           call Galacticus_Error_Report(message//{introspection:location})
        end if
        ! Adjust the mass to that of the parent node.
        call basic%massSet         (basicParent%mass         ())
        ! Adjust the accretion rate to that of the parent node.
        call basic%accretionRateSet(basicParent%accretionRate())
     end select
     return
   end subroutine Node_Component_Basic_Standard_Promote

  double precision function Node_Component_Basic_Standard_Unresolved_Mass(node)
    !% Return the unresolved mass for {\normalfont \ttfamily node}.
    implicit none
    type (treeNode          ), intent(inout), pointer :: node
    type (treeNode          )               , pointer :: nodeChild
    class(nodeComponentBasic)               , pointer :: basicChild, basic

    ! Get the basic component.
    basic => node%basic()
    ! Initialize the unresolved mass to the mass of the current node's basic component.
    Node_Component_Basic_Standard_Unresolved_Mass=basic%mass()
    ! Remove the mass of all child nodes.
    nodeChild => node%firstChild
    do while (associated(nodeChild))
       basicChild                                    => nodeChild%basic()
       Node_Component_Basic_Standard_Unresolved_Mass =  Node_Component_Basic_Standard_Unresolved_Mass-basicChild%mass()
       nodeChild                                     => nodeChild%sibling
    end do
    return
  end function Node_Component_Basic_Standard_Unresolved_Mass

  !# <radiusSolverPlausibility>
  !#  <unitName>Node_Component_Basic_Standard_Plausibility</unitName>
  !# </radiusSolverPlausibility>
  subroutine Node_Component_Basic_Standard_Plausibility(node)
    !% Determines whether the disk is physically plausible for radius solving tasks. Require that it have non-zero mass and angular momentum.
    implicit none
    type   (treeNode          ), intent(inout) :: node
    class  (nodeComponentBasic), pointer       :: basic

    basic => node%basic()
    select type (basic)
    class is (nodeComponentBasicStandard)
       if (basic%mass() <= 0.0d0 .or. basic%time() <= 0.0d0) then
          node%isPhysicallyPlausible=.false.
          node%isSolvable           =.false.
       end if
    end select
    return
  end subroutine Node_Component_Basic_Standard_Plausibility
  
end module Node_Component_Basic_Standard
