import unreal_engine as ue
from pathlib import Path
import asyncio

from lambda_server import LambdaServer

"""Liason class between Python and Unreal that allows hooking into the world tick"""

print('Loading DummyPyActor')

try:
    import zmq
    import pyarrow

    START_UNREAL_API_SERVER = True
    print('Starting UnrealPython server on zmq!')
except ImportError:
    START_UNREAL_API_SERVER = False
    CURR_PATH = Path(__file__).resolve().parent
    print('To enable the UnrealPython API, start the sim '
          '\n\tthrough the deepdrive project (github.com/deepdrive/deepdrive)'
          '\n\tand enter %s'
          '\n\tas the simulator project directory when prompted.'
          '\n\tAlternately, you can download the dependencies from'
          '\n\thttps://s3-us-west-1.amazonaws.com/deepdrive/unreal_python_lib/python_libs.zip'
          '\n\tand extract into <your-project-root>/python_libs' % CURR_PATH)


class DummyPyActor:

    def __init__(self):
        self.worlds = None
        self.world = None
        self.ai_controllers = None
        self.started_server = False

    def begin_play(self):
        print('Begin Play on DummyPyActor class')
        self._find_world()

    def tick(self, delta_time):
        if self.world is None:
            self._find_world()
        elif not self.started_server:
            asyncio.ensure_future(LambdaServer().run(self.world))
            self.started_server = True

    def _find_world(self):
        self.worlds = ue.all_worlds()
        # print('All worlds length ' + str(len(self.worlds)))

        # print([w.get_full_name() for w in self.worlds])

        if hasattr(ue, 'get_editor_world'):
            # print('Detected Unreal Editor')
            self.worlds.append(ue.get_editor_world())
        else:
            # print('Determined we are in a packaged game')
            # self.worlds.append(self.uobject.get_current_level()) # A LEVEL IS NOT A WORLD
            pass

        self.worlds = [w for w in self.worlds if 'DeepDriveSim_Demo.DeepDriveSim_Demo' in w.get_full_name()]

        for w in self.worlds:
            self.ai_controllers = [a for a in w.all_actors()
                                   if 'LocalAIController_'.lower() in a.get_full_name().lower()]
            if self.ai_controllers:
                self.world = w
                print('Found current world')
                break
        else:
            # print('Current world not detected')
            pass

        return self.world


