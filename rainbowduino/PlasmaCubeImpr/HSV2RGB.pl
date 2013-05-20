#!/usr/bin/perl

# Dependencies:
# - Graphics::Color

# Ways to install
#
# (Debian)
# sudo apt-get install 
# 
# (Perl cpanminus)
# sudo cpan App::cpanminus
# sudo /opt/local/libexec/perl5.12/sitebin/cpanm Graphics::Color
#  ^^ but this errored out before completing
#
# (Perl classic CPAN)
# sudo perl -MCPAN -e "shell"
# cpan> install Graphics::Color
#

#HSV2RGB.pl
use Graphics::Color::HSV;
use POSIX qw(ceil floor);

$red="";
$green="";
$blue="";

$SIZE_OF_GRADIENT = 2 ** 6;
$count = 0;

for($hu = 0.0; $hu <360.0 ; $hu=$hu+(360.0/$SIZE_OF_GRADIENT))
{
    $count = $count + 1;

    my $color = Graphics::Color::HSV->new({ hue => $hu, saturation  => 1, value  => 1,});
    $c = $color->to_rgb();
    $r = ceil($c->red * 255);
    $g = ceil($c->green * 255);
    $b = ceil($c->blue * 255);
    
    $red   .= $r . ',';
    $green .= $g . ',';
    $blue  .= $b . ',';

    warn ("count: $count {R,G,B} = { $r , $g , $b }\n");
}

print "unsigned char RED[64] = {$red};";
print "\n";
print "unsigned char GREEN[64] = {$green};";
print "\n";
print "unsigned char BLUE[64] = {$blue};";
print "\n";

if ($count != $SIZE_OF_GRADIENT) {
    warn "Error: miss-sized array on output\n";
}
