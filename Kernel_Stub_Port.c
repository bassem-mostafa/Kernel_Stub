// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

#include "Platform.h"

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#ifdef KERNEL_STUB

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

    #include "../../Kernel_Internal.h"
    #include "Kernel_Stub_Port.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef struct KERNEL_Task_Instance_t KERNEL_Task_Instance_t;

typedef struct KERNEL_Task_Instance
{
    KERNEL_Task_t * Task;
    KERNEL_Task_Instance_t * Next;
} KERNEL_Task_Instance_t;

typedef struct KERNEL_Instance_Context
{
    KERNEL_Task_Instance_t * Root;
} KERNEL_Instance_Context;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

KERNEL_Status_t KERNEL_Instance_Initialize( KERNEL_Instance_t * KERNEL_Instance )
{
    KERNEL_Status_t KERNEL_Status = KERNEL_Status_Error;
    do
    {
        KERNEL_Trace( "%s( Instance=%p )", __FUNCTION__, KERNEL_Instance );
        if ( ( KERNEL_Status = KERNEL_Instance_IsValid( KERNEL_Instance ) ) != KERNEL_Status_Success )
        {
            break;
        }
        if ( KERNEL_Instance->Context == NULL )
        {
            RAM_Status_t RAM_Status = RAM_Status_Error;
            if ( ( RAM_Status = RAM_Allocate( RAM_1, ( RAM_Reference_t * ) &KERNEL_Instance->Context, UTIL_SizeOf( KERNEL_Instance_Context_t ) ) ) != RAM_Status_Success )
            {
                KERNEL_Status = KERNEL_Status_Error;
                break;
            }
            KERNEL_Instance->Context->Root = NULL;
        }
        if ( KERNEL_Instance->Context->Root != NULL )
        {
            // FIXME
        }
        KERNEL_Status = KERNEL_Status_Success;
    }
    while ( 0 );
    return KERNEL_Status;
}

KERNEL_Status_t KERNEL_Instance_Cycle( KERNEL_Instance_t * KERNEL_Instance )
{
    KERNEL_Status_t KERNEL_Status = KERNEL_Status_Error;
    do
    {
        KERNEL_Trace( "%s( Instance=%p )", __FUNCTION__, KERNEL_Instance );
        if ( ( KERNEL_Status = KERNEL_Instance_IsValid( KERNEL_Instance ) ) != KERNEL_Status_Success )
        {
            break;
        }
        KERNEL_Task_Instance_t * KERNEL_Task_Instance = KERNEL_Instance->Context->Root;
        while ( KERNEL_Task_Instance )
        {
            if ( KERNEL_Task_Instance->Task->Cycle != NULL )
            {
                if ( KERNEL_Task_Instance->Task->Cycle( ) != KERNEL_Status_Success )
                {
                    // FIXME
                }
            }
            KERNEL_Task_Instance = KERNEL_Task_Instance->Next;
        }
        // Nothing to be done
        KERNEL_Status = KERNEL_Status_Success;
    }
    while ( 0 );
    return KERNEL_Status;
}

KERNEL_Status_t KERNEL_Instance_DeInitialize( KERNEL_Instance_t * KERNEL_Instance )
{
    KERNEL_Status_t KERNEL_Status = KERNEL_Status_Error;
    do
    {
        KERNEL_Trace( "%s( Instance=%p )", __FUNCTION__, KERNEL_Instance );
        if ( ( KERNEL_Status = KERNEL_Instance_IsValid( KERNEL_Instance ) ) != KERNEL_Status_Success )
        {
            break;
        }
        if ( KERNEL_Instance->Context != NULL )
        {
            // FIXME
        }
        KERNEL_Status = KERNEL_Status_Success;
    }
    while ( 0 );
    return KERNEL_Status;
}

KERNEL_Status_t KERNEL_Instance_TaskCreate( KERNEL_Instance_t * KERNEL_Instance, KERNEL_Task_t * KERNEL_Task )
{
    KERNEL_Status_t KERNEL_Status = KERNEL_Status_Error;
    do
    {
        KERNEL_Trace( "%s( Instance=%p, Task=%p )", __FUNCTION__, KERNEL_Instance, KERNEL_Task );
        if ( ( KERNEL_Status = KERNEL_Instance_IsValid( KERNEL_Instance ) ) != KERNEL_Status_Success )
        {
            break;
        }
        KERNEL_Task_Instance_t * KERNEL_Task_Instance = NULL;
        RAM_Status_t RAM_Status = RAM_Status_Error;
        if ( ( RAM_Status = RAM_Allocate( RAM_1, ( RAM_Reference_t * ) &KERNEL_Task_Instance, UTIL_SizeOf( KERNEL_Task_Instance_t ) ) ) != RAM_Status_Success )
        {
            KERNEL_Status = KERNEL_Status_Error;
            break;
        }
        KERNEL_Task_Instance->Task = KERNEL_Task;
        KERNEL_Task_Instance->Next = NULL;

        if ( KERNEL_Instance->Context->Root == NULL )
        {
            KERNEL_Instance->Context->Root = KERNEL_Task_Instance;
        }
        else
        {
            KERNEL_Task_Instance_t * KERNEL_Task_Instance_Last = KERNEL_Instance->Context->Root;
            while ( KERNEL_Task_Instance_Last->Next != NULL )
            {
                KERNEL_Task_Instance_Last = KERNEL_Task_Instance_Last->Next;
            }
            KERNEL_Task_Instance_Last->Next = KERNEL_Task_Instance;
        }
        if ( KERNEL_Task_Instance->Task->Initialize != NULL )
        {
            if ( KERNEL_Task_Instance->Task->Initialize( ) != KERNEL_Status_Success )
            {
                // FIXME
            }
        }
        KERNEL_Status = KERNEL_Status_Success;
    }
    while ( 0 );
    return KERNEL_Status;
}

KERNEL_Status_t KERNEL_Instance_TaskDestroy( KERNEL_Instance_t * KERNEL_Instance, KERNEL_Task_t * KERNEL_Task )
{
    KERNEL_Status_t KERNEL_Status = KERNEL_Status_Error;
    do
    {
        KERNEL_Trace( "%s( Instance=%p, Task=%p )", __FUNCTION__, KERNEL_Instance, KERNEL_Task );
        if ( ( KERNEL_Status = KERNEL_Instance_IsValid( KERNEL_Instance ) ) != KERNEL_Status_Success )
        {
            break;
        }
        KERNEL_Task_Instance_t * KERNEL_Task_Instance_Previous = NULL;
        KERNEL_Task_Instance_t * KERNEL_Task_Instance = KERNEL_Instance->Context->Root;
        while ( ( KERNEL_Task_Instance != NULL ) && ( KERNEL_Task_Instance->Task != KERNEL_Task ) )
        {
            KERNEL_Task_Instance_Previous = KERNEL_Task_Instance;
            KERNEL_Task_Instance = KERNEL_Task_Instance->Next;
        }
        if ( KERNEL_Task_Instance != NULL )
        {
            if ( KERNEL_Task_Instance_Previous == NULL )
            {
                KERNEL_Instance->Context->Root = KERNEL_Task_Instance->Next;
            }
            else
            {
                KERNEL_Task_Instance_Previous->Next = KERNEL_Task_Instance->Next;
            }
            if ( KERNEL_Task_Instance->Task->DeInitialize != NULL )
            {
                if ( KERNEL_Task_Instance->Task->DeInitialize( ) != KERNEL_Status_Success )
                {
                    // FIXME
                }
            }
            RAM_Status_t RAM_Status = RAM_Status_Error;
            if ( ( RAM_Status = RAM_DeAllocate( RAM_1, ( RAM_Reference_t * ) &KERNEL_Task_Instance ) ) != RAM_Status_Success )
            {
                KERNEL_Status = KERNEL_Status_Error;
                break;
            }
        }
        KERNEL_Status = KERNEL_Status_Success;
    }
    while ( 0 );
    return KERNEL_Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* KERNEL_STUB */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
