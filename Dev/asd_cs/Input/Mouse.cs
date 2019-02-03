﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace asd
{
    /// <summary>
    /// マウスからの入力を取得するクラス
    /// </summary>
    public partial class Mouse
    {
        private SideButton leftButton;
        private SideButton rightButton;
        private MiddleButton middleButton;

        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="m">ネイティブインタフェース</param>
        internal Mouse(asd.swig.Mouse m)
        {
			CoreInstance = m;
            leftButton = new SideButton();
            rightButton = new SideButton();
            middleButton = new MiddleButton();
        }

        internal void RefreshAllState()
        {
			ButtonState mstate = (ButtonState)CoreInstance.GetLeftButton().GetButtonState();
            leftButton.SetState(mstate);

			mstate = (ButtonState)CoreInstance.GetRightButton().GetButtonState();
            rightButton.SetState(mstate);

			mstate = (ButtonState)CoreInstance.GetMiddleButton().GetButtonState();
			float rot = CoreInstance.GetMiddleButton().GetRotation();
            middleButton.SetState(mstate, rot);
        }

        /// <summary>
        /// 左ボタンの状態を返すプロパティ
        /// </summary>
        public SideButton LeftButton {
            get
            {
                return leftButton;
            }
        }

        /// <summary>
        /// 右ボタンの状態を返すプロパティ
        /// </summary>
        public SideButton RightButton
        {
            get
            {
                return rightButton;
            }
        }

        /// <summary>
        /// 中ボタンの状態を返すプロパティ
        /// </summary>
        public MiddleButton MiddleButton
        {
            get
            {
                return middleButton;
            }
        }


    }
}
