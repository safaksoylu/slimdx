/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#pragma once

#include "Device.h"

#include "Direct3DEx.h"
#include "DisplayModeEx.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D9
	{
#ifdef XMLDOCS
		ref class ResultCode;
#endif

		public enum class DeviceState : System::Int32
		{
			Ok = D3D_OK,
			DeviceLost = D3DERR_DEVICELOST,
			DeviceHung = D3DERR_DEVICEHUNG,
			DeviceRemoved = D3DERR_DEVICEREMOVED,
			OutOfVideoMemory = D3DERR_OUTOFVIDEOMEMORY,
			PresentModeChanged = S_PRESENT_MODE_CHANGED,
			PresentOccluded = S_PRESENT_OCCLUDED
		};

		public enum class ResourceResidency : System::Int32
		{
			Resident = S_OK,
			ResidentInSharedMemory = S_RESIDENT_IN_SHARED_MEMORY,
			NotResident = S_NOT_RESIDENT
		};

		ref class Resource;

		/// <summary>
		/// Applications use the methods of DeviceEx to render primitives, create resources, work with
		/// system-level variables, adjust gamma ramp levels, work with palettes, and create shaders.
		/// </summary>
		/// <unmanaged>IDirect3DDevice9Ex</unmanaged>
		public ref class DeviceEx : Device
		{
			COMOBJECT(IDirect3DDevice9Ex, DeviceEx);

		private:
			void Internal_Constructor( Direct3DEx^ direct3D, int adapter, DeviceType deviceType, System::IntPtr controlHandle,
				CreateFlags createFlags, PresentParameters^ presentParameters, D3DDISPLAYMODEEX* fullscreenDisplayMode );

		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::Direct3D9::DeviceEx"/> class.
			/// </summary>
			/// <param name="direct3D">The Direct3DEx instance to create the device from.</param>
			/// <param name="adapter">Ordinal number that denotes the display adapter.</param>
			/// <param name="deviceType">Denotes the desired device type. If the desired device type is not available, device creation will fail.</param>
			/// <param name="controlHandle">Specifies the target window for Direct3D rendering.</param>
			/// <param name="createFlags">Combination of one or more options that control device creation.</param>
			/// <param name="presentParameters">Describes the presentation parameters for the device being created.</param>
			DeviceEx( Direct3DEx^ direct3D, int adapter, DeviceType deviceType, System::IntPtr controlHandle,
				CreateFlags createFlags, PresentParameters^ presentParameters );

			/// <summary>
			/// Initializes a new instance of the <see cref="SlimDX::Direct3D9::DeviceEx"/> class.
			/// </summary>
			/// <param name="direct3D">The Direct3D instance to create the device from.</param>
			/// <param name="adapter">Ordinal number that denotes the display adapter.</param>
			/// <param name="deviceType">Denotes the desired device type. If the desired device type is not available, device creation will fail.</param>
			/// <param name="controlHandle">Specifies the target window for Direct3D rendering.</param>
			/// <param name="createFlags">Combination of one or more options that control device creation.</param>
			/// <param name="presentParameters">Describes the presentation parameters for the device being created.</param>
			/// <param name="fullscreenDisplayMode">The display mode for when the device is set to fullscreen.</param>
			DeviceEx( Direct3DEx^ direct3D, int adapter, DeviceType deviceType, System::IntPtr controlHandle,
				CreateFlags createFlags, PresentParameters^ presentParameters, DisplayModeEx fullscreenDisplayMode );

			/// <summary>
			/// Constructs a new instance of the <see cref="DeviceEx"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IDirect3DDevice9Ex pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static DeviceEx^ FromPointer( System::IntPtr pointer );

			property int GpuThreadPriority
			{
				int get();
				void set( int priority );
			};

			property int MaximumFrameLatency
			{
				int get();
				void set( int maxLatency );
			};

			/// <summary>
			/// Reports the current cooperative-level status of the Direct3D device for a windowed or full-screen application.
			/// </summary>
			/// <param name="windowHandle">The destination window handle to check for occlusion. This parameter may be IntPtr.Zero</param>
			/// <returns>The current status of this device.</returns>
			/// <remarks>This method replaces the <see cref="SlimDX::Direct3D9::Device" />.TestCooperativeLevel function,
			/// which always returns <see cref="SlimDX::Direct3D9::ResultCode" />.Success in Direct3D 9Ex applications.</remarks>
			DeviceState CheckDeviceState( System::IntPtr windowHandle );

			/// <summary>
			/// Checks a resource to determine if it is likely that it will cause a large stall at
			/// Draw time because the system must make the resource GPU-accessible.
			/// </summary>
			/// <param name="resource">An resource to check the residency status of.</param>
			/// <returns>See the DirectX documentation.</returns>
			/// <remarks>See the DirectX documentation.</remarks>
			ResourceResidency CheckResourceResidency( Resource^ resource );

			/// <summary>
			/// Checks an array of resources to determine if it is likely that they will cause a large stall at
			/// Draw time because the system must make the resources GPU-accessible.
			/// </summary>
			/// <param name="resources">An array of resources to check the residency status of.</param>
			/// <returns>See the DirectX documentation.</returns>
			/// <remarks>See the DirectX documentation.</remarks>
			ResourceResidency CheckResourceResidency( array<Resource^>^ resources );

			/// <summary>
			/// Retrieves the display mode's spatial resolution, color resolution, and refresh frequency.
			/// </summary>
			/// <param name="swapChain">The swap chain to retrieve display mode data about.</param>
			/// <returns>Extended display mode information about the adapter.</returns>
			DisplayModeEx GetDisplayModeEx( int swapChain );

			/// <summary>
			/// Retrieves the display mode's spatial resolution, color resolution, refresh frequency, and rotation settings.
			/// </summary>
			/// <param name="swapChain">The swap chain to retrieve display mode data about.</param>
			/// <param name="rotation">Receives the rotation setting of the adapter.</param>
			/// <returns>Extended display mode information about the adapter.</returns>
			DisplayModeEx GetDisplayModeEx( int swapChain, [Out] DisplayRotation% rotation );

			/// <summary>
			/// Swap the swapchain's next buffer with the front buffer.
			/// </summary>
			/// <param name="flags">Flags used to specify how the swap chain should be presented.</param>
			/// <returns>A <see cref="SlimDX::Result"/>Object describing the result of the operation.</returns>
			Result PresentEx( SlimDX::Direct3D9::Present flags );

			/// <summary>
			/// Swap the swapchain's next buffer with the front buffer.
			/// </summary>
			/// <param name="windowOverride">The destination window whose client area is taken as the target for this presentation.</param>
			/// <param name="flags">Flags used to specify how the swap chain should be presented.</param>
			/// <returns>A <see cref="SlimDX::Result"/>Object describing the result of the operation.</returns>
			Result PresentEx( System::IntPtr windowOverride, SlimDX::Direct3D9::Present flags );
			
			/// <summary>
			/// Resets the device.
			/// </summary>
			/// <param name="presentParameters">A set of new presentation parameters to apply to the device.</param>
			/// <returns>A <see cref="SlimDX::Result"/>Object describing the result of the operation.</returns>
			Result ResetEx( PresentParameters^ presentParameters );

			/// <summary>
			/// Resets the device.
			/// </summary>
			/// <param name="presentParameters">A set of new presentation parameters to apply to the device.</param>
			/// <param name="fullscreenDisplayMode">The properties of the desired display mode, when running fullscreen.</param>
			/// <returns>A <see cref="SlimDX::Result"/>Object describing the result of the operation.</returns>
			Result ResetEx( PresentParameters^ presentParameters, DisplayModeEx fullscreenDisplayMode );

			/// <summary>
			/// Suspend execution of the calling thread until the next vertical blank signal.
			/// </summary>
			/// <param name="swapChain">Zero based swap chain index to specify the target chain on a multihead card.</param>
			void WaitForVBlank( int swapChain );
		};
	}
}