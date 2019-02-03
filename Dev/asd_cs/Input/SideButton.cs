﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace asd
{
    /// <summary>
    /// マウスの左右ボタンの状態を扱うクラス
    /// </summary>
    public class SideButton
    {
        /// <summary>
        /// 押下状態を保持する変数
        /// </summary>
        private ButtonState mouseButtonState;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        internal SideButton() { }

        /// <summary>
        /// ボタンの押し状態をセットする関数
        /// </summary>
        /// <param name="mButtonState">押し状態</param>
        internal void SetState(ButtonState mButtonState)
        {
            mouseButtonState=mButtonState;
        }

        /// <summary>
        /// ボタンの押し状態を返すプロパティ
        /// </summary>
        public ButtonState ButtonState
        {
            get { return mouseButtonState; }
        }
    }
}
