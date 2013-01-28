jQuery(document).ready(
function($){
 
$('.collapseButton').click(function(){
$(this).parent().parent().find('.xContent').removeClass("xContent");
$('.xContent').slideUp('slow');
$(this).parent().parent().find('div:last').addClass("xContent");
$(this).parent().parent().find('.xContent').slideToggle('slow');
});
 
});
