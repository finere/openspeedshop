////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
// Copyright (c) 2006-2012 Krell Institute All Rights Reserved.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
// details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////


/*! \class ControlObject
    The is the message object passed to the owner Panel. 
    It is used to send the user's selected process control actions.

 */
#include <cstddef>
#include "ControlObject.hxx"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debug.hxx"

/*! Unused constructor. */
ControlObject::ControlObject() : MessageObject("ControlObject")
{
  nprintf( DEBUG_CONST_DESTRUCT ) ("ControlObject::ControlObject(entered.\n");
  cot = NONE_T;
}

/*! Initialize a control object message with a message type. */
ControlObject::ControlObject(ControlObjectType _cot) : MessageObject("ControlObject")
{
  nprintf( DEBUG_CONST_DESTRUCT ) ("ControlObject::ControlObject(entered.\n");
  cot = _cot;
}

/*! Destructor.   */
ControlObject::~ControlObject()
{
}

/*! Prints the objects fields.    Debug only. */
void
ControlObject::print()
{
  dprintf("ControlObject:\n");

  dprintf("	control object type: %d\n", cot);
}
