/**
 * Created by yangh on 2016/09/04.
 */
var main = {};
var myScroll;
(function ($) {
    main.init = function () {
        document.addEventListener('touchmove', function (e) {
            e.preventDefault();
        }, false);

        main.initEvent();
    };

    main.initEvent = function() {
        $(".pay-select > div").on("click", function()
        {
            $(".pay-select > div").removeClass("checked");
            $(this).addClass("checked");
        })
    };

    /**
     * @func move()
     * @desc 监听滚动条的位置，异步加载列表
     */
    function move() {
        // if (!canLoad) {
        //     return;
        // }

        if (myScroll.y < main.max - 50) {
            // canLoad = false;

            var html = "";
            for (var i = 0; i < 10; i++) {
                html += ' <li><a href="javascript:void(0);"><div class="fImg"><img src="../../images/f_8.png" alt=""></div><h3>男神海底捞（深圳店）</h3><p><i class="fa fa-star" aria-hidden="true"></i><i class="fa fa-star" aria-hidden="true"></i><i class="fa fa-star" aria-hidden="true"></i><i class="fa fa-star" aria-hidden="true"></i><i class="fa fa-star-half-o" aria-hidden="true"></i></p><p>海底捞100元优惠劵</p></a></li>';
            }
            $("#storeList").append(html);
            myScroll.refresh();
            main.max = myScroll.maxScrollY;
            // canLoad = true;
            console.log(main.max);
        }
    }

    /**
     * @func main.scroll()
     * @desc 配置iscroll插件
     */
    main.scroll = function () {
        myScroll = new IScroll(".storeList", {
            probeType: 3,
            mouseWheel: true,
            click: true,
            preventDefault: false
        });

        main.max = myScroll.maxScrollY;
        console.log(main.max);

        myScroll.on("scroll", move);
    };
})(jQuery);

main.init();

window.onload = function () {
    main.scroll();
};