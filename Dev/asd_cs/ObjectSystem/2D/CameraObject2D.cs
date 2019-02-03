﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace asd
{
    /// <summary>
    /// 2Dレイヤーの一部を描画するためのカメラ
    /// </summary>
    public class CameraObject2D : Object2D, IReleasable
    {
        /// <summary>
        /// この2Dオブジェクトを描画する際の描画優先度を取得または設定する。描画優先度が高いほど手前に描画される。
        /// </summary>
		public int DrawingPriority
        {
            get { return coreCameraObject.GetDrawingPriority(); }
            set { coreCameraObject.SetDrawingPriority(value); }
        }

        /// <summary>
        /// 描画元の領域を取得、または設定する。
        /// </summary>
        public RectI Src
        {
            get { return coreCameraObject.GetSrc(); }
            set { coreCameraObject.SetSrc(value); }
        }

        /// <summary>
        /// 描画先の領域を取得、または設定する。
        /// </summary>
        public RectI Dst
        {
            get { return coreCameraObject.GetDst(); }
            set { coreCameraObject.SetDst(value); }
        }

        /// <summary>
        /// 画面に描画せずにテクスチャに描画するか、を取得または設定する。
        /// </summary>
        public bool IsOffsecreenMode
        {
            get { return coreCameraObject.GetIsOffscreenMode(); }
            set { coreCameraObject.SetIsOffscreenMode(value); }
        }

        /// <summary>
        /// カメラが描画した結果をテクスチャとして取得する。
        /// </summary>
        public Texture2D Texture
        {
            get { return GC.GenerateTexture2D(coreCameraObject.GetTexture(), GenerationType.Get); }
        }

        ///<summary>
        /// カメラが描画した結果を描画する際のテクスチャフィルタを取得または設定する。
        /// </summary>
        public TextureFilterType TextureFilterType
        {
            get { return (TextureFilterType)coreCameraObject.GetTextureFilterType(); }
            set { coreCameraObject.SetTextureFilterType((swig.TextureFilterType)value); }
        }

        internal override swig.CoreObject2D CoreObject
        {
            get { return coreCameraObject; }
        }
        private swig.CoreCameraObject2D coreCameraObject { get; set; }

        public CameraObject2D()
        {
            coreCameraObject = Engine.ObjectSystemFactory.CreateCameraObject2D();

            var p = coreCameraObject.GetPtr();
            if (GC.Object2Ds.GetObject(p) != null)
            {
                Particular.Helper.ThrowException("");
            }

            GC.Object2Ds.AddObject(p, this);
        }

        #region GC対策
        ~CameraObject2D()
        {
            ForceToRelease();
        }

        public override bool IsReleased
        {
            get { return coreCameraObject == null; }
        }

        /// <summary>
        /// 強制的に使用しているメモリを開放する。
        /// </summary>
        /// <remarks>
        /// 何らかの理由でメモリが不足した場合に実行する。
        /// 開放した後の動作の保証はしていないので、必ず参照が残っていないことを確認する必要がある。
        /// </remarks>
        public override void ForceToRelease()
        {
            lock (this)
            {
                if (coreCameraObject == null) return;
                GC.Collector.AddObject(coreCameraObject);
                coreCameraObject = null;
            }
            Particular.GC.SuppressFinalize(this);
        }
        #endregion
    }
}
